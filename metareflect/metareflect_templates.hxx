/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_TEMPLATES_HXX
#define METAREFLECT_TEMPLATES_HXX
#pragma once
#ifndef __METAREFLECT__

#include <vector>
#include <string>

namespace metareflect
{
namespace detail
{

/* ========================================================================= */
/* Vector                                                                    */
/* ========================================================================= */
template<class VecT>
struct VectorClass : public ClassTemplate
{
    using ClassTemplate::ClassTemplate;

    virtual void
    Visit(
        void const *instance,
        ClassVisitor *visitor,
        size_t filter = Field::kFlagsSerialized,
        unsigned depth = 0) const noexcept
    {
        if (instance == nullptr) {
            visitor->Primitive(this, nullptr);
            return;
        }

        Type const *type = GetType<typename VecT::value_type>();
        VecT const *vec = (VecT const *)instance;

        visitor->ArrayBegin(this, depth, vec->size());
        size_t i = 0;
        for (auto const &e : *vec) {
            visitor->ArrayElement(type, depth + 1, i++);

            if (type->IsClass()) {
                Class const *c = (Class const *)type;
                c->Visit(&e, visitor, filter, depth + 1);
            } else {
                visitor->Primitive(type, &e);
            }
        }
        visitor->ArrayEnd(this, depth);
    }
};

template<class T>
inline Class const *
GetClassImpl(ClassTag<std::vector<T>>) noexcept
{
    static ClassStorage<T, 0, 0, 1> reflected([](auto self) {
        self->templateArgs[0].tag = TemplateArgument::Tag::Type;
        self->templateArgs[0].type = GetType<T>();
    });
    static VectorClass<std::vector<T>> cache(
        sizeof(std::vector<T>),
        Hash("std::vector<T>"),
        nullptr,/* BASECLASS */
        reflected.fields,
        reflected.fields + reflected.numFields,
        reflected.functions,
        reflected.functions + reflected.numFunctions,
        "std::vector<T>",
        Class::kFlagsNull,
        reflected.templateArgs,
        reflected.templateArgs + reflected.numTemplateArgs
    );
    return &cache;
}

template<class T>
inline Type const *
GetTypeImpl(TypeTag<std::vector<T>>) noexcept
{
    return GetClassImpl(ClassTag<std::vector<T>>{});
}


/* ========================================================================= */
/* String                                                                    */
/* ========================================================================= */
class StringClass : public Class
{
    using Class::Class;

    virtual void
    Visit(
        void const *instance,
        ClassVisitor *visitor,
        size_t filter = Field::kFlagsSerialized,
        unsigned depth = 0) const noexcept
    {
        if (instance == nullptr) {
            visitor->String(this, nullptr);
            return;
        }

        std::string const *str = (std::string const *)instance;
        char const *s = str->c_str();
        visitor->String(this, &s);
    }
};

inline Class const *
GetClassImpl(ClassTag<std::string>) noexcept
{
    static ClassStorage<std::string, 0, 0, 0> reflected([](auto self) {
    });
    static StringClass cache(
        sizeof(std::string),
        Hash("std::string"),
        nullptr,/* BASECLASS */
        reflected.fields,
        reflected.fields + reflected.numFields,
        reflected.functions,
        reflected.functions + reflected.numFunctions,
        "std::string",
        Class::kFlagsNull
    );
    return &cache;
}

inline Type const *
GetTypeImpl(TypeTag<std::string>) noexcept
{
    return GetClassImpl(ClassTag<std::string>{});
}


} /* namespace detail */
} /* namespace metareflect */

#endif /* ifndef __METAREFLECT__ */
#endif /* METAREFLECT_TEMPLATES_HXX */

