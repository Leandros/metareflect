/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */
#ifndef METAREFLECT_DETAIL_HXX
#define METAREFLECT_DETAIL_HXX
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <vector>
#include "metareflect.hxx"

namespace metareflect
{

/* Forward declare storages, for friend declarations. */
namespace detail
{

template<class Type, size_t NFields, size_t NFunctions, size_t NTemplateArgs = 0>
struct ClassStorage;

template<size_t NParameter>
struct FunctionStorage;

template<class T>
Class const *
GetClassImpl(ClassTag<T>) noexcept;

template<class T>
Type const *
GetTypeImpl(TypeTag<T>) noexcept;

} /* namespace detail */


/* ========================================================================= */
/* Hash                                                                      */
/* ========================================================================= */
static constexpr uint64_t kFNV1aValue = 0xcbf29ce484222325;
static constexpr uint64_t kFNV1aPrime = 0x100000001b3;

inline constexpr uint64_t
Hash(char const * const str, uint64_t const value = kFNV1aValue) noexcept
{
    return (str[0] == '\0') 
        ? value 
        : Hash(&str[1], (value ^ uint64_t(str[0])) * kFNV1aPrime);
}


/* ========================================================================= */
/* Iterator Wrapper                                                          */
/* ========================================================================= */
template<class T>
class ForEach
{
public:
    ForEach(T const *_begin, T const *_end) noexcept
        : m_begin(_begin)
        , m_end(_end)
    {}

    T const *
    begin() const noexcept
    {
        return m_begin;
    }

    T const *
    end() const noexcept
    {
        return m_end;
    }

    size_t
    Length() const noexcept
    {
        return m_end - m_begin;
    }

    T const &
    operator[](size_t idx) const noexcept
    {
        return m_begin[idx];
    }

protected:
    T const *m_begin;
    T const *m_end;
};


/* ========================================================================= */
/* Types                                                                     */
/* ========================================================================= */

/* ===-------------------------------------------------------------------=== */
/* Qualifier                                                                 */
/* ===-------------------------------------------------------------------=== */
enum CVQualifier : unsigned char {
    kCVQualifierNone            = 0x0,
    kCVQualifierConst           = 0x1,
    kCVQualifierVolatile        = 0x2,
    kCVQualifierConstVolatile   = (kCVQualifierConst | kCVQualifierVolatile),
};

enum RefQualifier : unsigned char {
    kRefQualifierNone   = 0x0,
    kRefQualifierRef    = 0x1,
    kRefQualifierRefRef = 0x2,
};

enum StorageClass : unsigned char {
    kStorageClassNone,
    kStorageClassExtern,
    kStorageClassStatic,
    kStorageClassExternThreadLocal,
    kStorageClassStaticThreadLocal,
    kStorageClassMember,
    kStorageClassStaticMember,
    kStorageClassThreadLocalStaticMember,
};

struct Qualifier {
    constexpr
    Qualifier(
        unsigned char cv = kRefQualifierNone,
        unsigned char ref = kRefQualifierNone,
        unsigned char storage = kStorageClassNone,
        unsigned char pointer = 0,
        unsigned char array = 0,
        unsigned count = 0) noexcept
        : arrayLength(count)
        , cvQualifier(cv)
        , refQualifier(ref)
        , storageClass(storage)
        , isPointer(pointer)
        , isArray(array)
    {}

    unsigned arrayLength;
    unsigned char cvQualifier : 3;
    unsigned char refQualifier : 3;
    unsigned char storageClass : 3;
    unsigned char isPointer : 1;
    unsigned char isArray : 1;
};


/* ===-------------------------------------------------------------------=== */
/* Type                                                                      */
/* ===-------------------------------------------------------------------=== */
/* All types inherit from 'Type' */
class Type
{
    template<class Type, size_t, size_t, size_t>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    Type() noexcept
        : m_size(0)
        , m_hash(0)
    {}

    Type(
        int size,
        uint64_t hash,
        char const *name) noexcept
        : m_size(size)
        , m_hash(hash)
        , m_name(name)
    {}

    /* --------------------------------------------------------------------- */
    /* Identifier                                                            */
    /* --------------------------------------------------------------------- */
    virtual bool IsClass() const noexcept { return false; };

    /* --------------------------------------------------------------------- */
    /* Access                                                                */
    /* --------------------------------------------------------------------- */
    uint64_t
    Size() const noexcept
    {
        return m_size;
    }

    uint64_t
    Hash() const noexcept
    {
        return m_hash;
    }

    char const *
    Name() const noexcept
    {
        return m_name;
    }

    virtual void
    Dump(void const *instance, FILE *file = stdout) const noexcept
    {
        fprintf(file, "%s{%p}", m_name, instance);
    }


    /* --------------------------------------------------------------------- */
    /* Operator                                                              */
    /* --------------------------------------------------------------------- */
    bool
    operator==(Type const &other) const noexcept
    {
        return m_hash == other.m_hash;
    }

    bool
    operator!=(Type const &other) const noexcept
    {
        return !(*this == other);
    }


public:
    uint64_t m_size;
    uint64_t m_hash;
    char const *m_name;
};


/* ===-------------------------------------------------------------------=== */
/* Field                                                                     */
/* ===-------------------------------------------------------------------=== */
/* All fields of classes are represented via this class. */
class Field
{
    template<class Type, size_t, size_t, size_t>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;
    friend class Class;

public:
    static constexpr unsigned kFlagsNull       = 0x0;
    static constexpr unsigned kFlagsSerialized = 0x1;
    static constexpr unsigned kFlagsCString    = 0x2;

    Field() noexcept = default;

    Field(
        Type const *type,
        unsigned flags,
        unsigned width,
        unsigned offset,
        Qualifier qualifier) noexcept
        : m_type(type)
        , m_flags(flags)
        , m_serializedWidth(width)
        , m_offset(offset)
        , m_qualifier(qualifier)
    {}

    /* --------------------------------------------------------------------- */
    /* Properties                                                            */
    /* --------------------------------------------------------------------- */
    metareflect::Type const *
    Type() const noexcept
    {
        return m_type;
    }

    unsigned
    Flags() const noexcept
    {
        return m_flags;
    }

    size_t
    SerializedWidth() const noexcept
    {
        return m_serializedWidth;
    }

    size_t
    Offset() const noexcept
    {
        return m_offset;
    }

    metareflect::Qualifier const &
    Qualifier() const noexcept
    {
        return m_qualifier;
    }

    char const *
    Name() const noexcept
    {
        return m_name;
    }


    /* --------------------------------------------------------------------- */
    /* Access                                                                */
    /* --------------------------------------------------------------------- */
    template<class T>
    void
    SetValue(void *instance, T const &value) const noexcept
    {
        /* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
        memcpy(((char *)instance + m_offset), &value, sizeof(T));
    }

    template<class T>
    T
    GetAs(void const *instance) const noexcept
    {
        /* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
        T ret;
        memcpy(&ret, ((char *)instance + m_offset), sizeof(T));
        return ret;
    }

    template<class T>
    T const *
    GetPointer(void const *instance) const noexcept
    {
        /* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
        return static_cast<T const *>((char *)instance + m_offset);
    }

    template<class T>
    T *
    GetPointer(void *instance) const noexcept
    {
        /* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
        return static_cast<T *>((char *)instance + m_offset);
    }

    void const *
    GetVoidPointer(void const *instance) const noexcept
    {
        return static_cast<void const *>((char *)instance + m_offset);
    }


public:
    metareflect::Type const *m_type;
    unsigned m_flags;
    unsigned m_serializedWidth;
    unsigned m_offset;
    metareflect::Qualifier m_qualifier;
    char const *m_name;
};


/* ===-------------------------------------------------------------------=== */
/* Function                                                                  */
/* ===-------------------------------------------------------------------=== */
/* ----- Function Parameter ------ */
class FunctionParameter : public Field
{
    template<class Type, size_t, size_t, size_t>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    /* Inherit constructor. */
    using Field::Field;
};

/* ----- Function Return ------ */
class FunctionReturn : public Field
{
    template<class Type, size_t, size_t, size_t>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    /* Inherit constructor. */
    using Field::Field;
};


/* ====== Function ====== */
class Function
{
    template<class Type, size_t, size_t, size_t>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    static constexpr unsigned kFlagsNull       = 0x0;
    static constexpr unsigned kFlagsMember     = 0x1;
    static constexpr unsigned kFlagsReplicated = 0x2;

    Function() noexcept = default;

    Function(
        FunctionReturn *returnType,
        /* TODO(arvid): Replace with parameter of range. */
        FunctionParameter *parameters,
        FunctionParameter *parametersEnd,
        unsigned flags) noexcept
        : m_returnType(returnType)
        , m_parameters(parameters)
        , m_parametersEnd(parametersEnd)
        , m_flags(flags)
    {}

    /* --------------------------------------------------------------------- */
    /* Properties                                                            */
    /* --------------------------------------------------------------------- */
    FunctionReturn const *
    ReturnType() const noexcept
    {
        return m_returnType;
    }

    /* TODO(arvid): Replace with 'a::Range'. */
    ForEach<FunctionParameter>
    Parameters() const noexcept
    {
        return ForEach<FunctionParameter>{m_parameters, m_parametersEnd};
    }

    unsigned
    Flags() const noexcept
    {
        return m_flags;
    }

    char const *
    Name() const noexcept
    {
        return m_name;
    }


public:
    FunctionReturn const *m_returnType;
    FunctionParameter const *m_parameters;
    FunctionParameter const *m_parametersEnd;
    unsigned m_flags;
    char const *m_name;
};


/* ===-------------------------------------------------------------------=== */
/* Enum                                                                      */
/* ===-------------------------------------------------------------------=== */
class Enum : public Type
{
    /* TODO(arvid): Implement enums. */
};


/* ===-------------------------------------------------------------------=== */
/* Class Visitor                                                             */
/* ===-------------------------------------------------------------------=== */
struct ClassVisitor
{
    virtual ~ClassVisitor() {}

    /* ===---------------------------------------------------------------=== */
    /* Class                                                                 */
    /* ===---------------------------------------------------------------=== */
    virtual void
    ClassBegin(Class const *, int depth) = 0;

    virtual void
    ClassEnd(Class const *, int depth) = 0;

    virtual void
    ClassMember(Field const *, int depth) = 0;

    /* ===---------------------------------------------------------------=== */
    /* Array                                                                 */
    /* ===---------------------------------------------------------------=== */
    virtual void
    ArrayBegin(Type const *, int depth, int length) = 0;

    virtual void
    ArrayEnd(Type const *, int depth) = 0;

    virtual void
    ArrayElement(Type const *type, int depth, int elem) = 0;

    /* ===---------------------------------------------------------------=== */
    /* Primitive Output                                                      */
    /* ===---------------------------------------------------------------=== */
    virtual void
    Primitive(Type const *t, void const *instance) = 0;
    virtual void
    String(Type const *t, void const *instance) = 0;
};


/* ===-------------------------------------------------------------------=== */
/* Class                                                                     */
/* ===-------------------------------------------------------------------=== */
/*
 * As of right now, the only root-type to be reflected are classes, annotated
 * with the 'CLASS' macro.
 * Support for free functions or free types may be added at a later point.
 */
class Class : public Type
{
    template<class T>
    friend Class const *GetClass() noexcept;
    template<class T>
    friend Type const *GetType() noexcept;
    template<class T>
    friend Class const *GetClassImpl(ClassTag<T>) noexcept;
    template<class T>
    friend Type const *GetTypeImpl(TypeTag<T>) noexcept;

public:
    static constexpr size_t kFlagsNull               = 0x0;
    static constexpr size_t kFlagsHasBeforeSerialize = 0x1;
    static constexpr size_t kFlagsHasAfterSerialize  = 0x2;
    static constexpr size_t kFlagsHasCustomSerialize = 0x4;
    static constexpr size_t kFlagsHasCustomDump      = 0x8;

public:
    Class(
        int size,
        uint64_t hash,
        Class *baseClass,
        /* TODO(arvid): Replace with parameter of range. */
        Field *fields,
        Field *fieldsEnd,
        /* TODO(arvid): Replace with parameter of range. */
        Function *functions,
        Function *functionsEnd,
        char const *name,
        size_t flags) noexcept
        : Type(size, hash, name)
        , m_baseClass(baseClass)
        , m_fields(fields)
        , m_fieldsEnd(fieldsEnd)
        , m_functions(functions)
        , m_functionsEnd(functionsEnd)
        , m_name(name)
        , m_flags(flags)
    {
        /* Any nullptr type is refering to ourself. */
        for (Field *field = fields; field != fieldsEnd; ++field)
            if (field->m_type == nullptr)
                field->m_type = this;
    }

    /* --------------------------------------------------------------------- */
    /* Identifier                                                            */
    /* --------------------------------------------------------------------- */
    virtual bool IsClass() const noexcept override { return true; };

    /* --------------------------------------------------------------------- */
    /* Identifier                                                            */
    /* --------------------------------------------------------------------- */
    void
    VisitField(
        void const *ptr,
        Field const *field,
        ClassVisitor *visitor,
        size_t filter,
        int depth,
        int arrayElem = -1) const noexcept
    {
        /* If the field isn't passing the filter, skip it. */
        if (!(field->Flags() & filter))
            return;

        Type const *type = field->Type();
        auto &qualifier = field->Qualifier();

        if (qualifier.isArray)
            visitor->ArrayElement(type, depth, arrayElem);
        else
            visitor->ClassMember(field, depth);

        /* Recurse deeper if the field is a class. */
        if (type->IsClass()) {
            Class const *c = (Class const *)type;

            /* Resolve pointers directly. */
            if (field->Qualifier().isPointer) {
                void const *p = *(void const **)ptr;
                c->Visit(p, visitor, filter, depth);
            } else {
                c->Visit(ptr, visitor, filter, depth);
            }
        }

        /* Just visit the field if it's a primitive. */
        else {
            if ((field->Flags() & Field::kFlagsCString))
                visitor->String(field->Type(), ptr);
            else
                visitor->Primitive(field->Type(), ptr);
        }
    }

    void
    VisitArray(
        void const *ptr,
        Field const *field,
        ClassVisitor *visitor,
        size_t filter,
        unsigned depth) const noexcept
    {
        /* If the field isn't passing the filter, skip it. */
        if (!(field->Flags() & filter))
            return;

        auto &qualifier = field->Qualifier();
        visitor->ClassMember(field, depth);
        visitor->ArrayBegin(field->Type(), depth, qualifier.arrayLength);

        char const *p = (char const *)ptr;
        for (int i = 0, n = qualifier.arrayLength; i < n; ++i) {
            VisitField(p, field, visitor, depth + 1, i);
            p += field->Type()->Size();
        }

        visitor->ArrayEnd(field->Type(), depth);
    }

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

        visitor->ClassBegin(this, depth);
        for (auto &field : Fields()) {
            void const *ptr = field.GetVoidPointer(instance);
            auto &qualifier = field.Qualifier();

            if (qualifier.isArray) {
                VisitArray(ptr, &field, visitor, filter, depth + 1);
            } else {
                VisitField(ptr, &field, visitor, filter, depth + 1);
            }
        }
        visitor->ClassEnd(this, depth);
    }


    /* --------------------------------------------------------------------- */
    /* Access                                                                */
    /* --------------------------------------------------------------------- */
    Class const *
    BaseClass() const noexcept
    {
        return m_baseClass;
    }

    /* TODO(arvid): Replace with 'a::Range' */
    ForEach<Field>
    Fields() const noexcept
    {
        return ForEach<Field>{m_fields, m_fieldsEnd};
    }

    ForEach<Function>
    Functions() const noexcept
    {
        return ForEach<Function>{m_functions, m_functionsEnd};
    }

    char const *
    Name() const noexcept
    {
        return m_name;
    }

    size_t
    Flags() const noexcept
    {
        return m_flags;
    }

    Field const *
    FieldByName(char const *name) const noexcept
    {
        for (auto &field : Fields()) {
            if (strcmp(name, field.Name()) == 0)
                return &field;
        }

        return nullptr;
    }

    Function const *
    FunctionByName(char const *name) const noexcept
    {
        for (auto &func : Functions()) {
            if (strcmp(name, func.Name()) == 0)
                return &func;
        }

        return nullptr;
    }

public:
    Class *m_baseClass;
    Field *m_fields;
    Field *m_fieldsEnd;
    Function *m_functions;
    Function *m_functionsEnd;
    char const *m_name;
    size_t m_flags;
};


/* ========================================================================= */
/* Templates                                                                 */
/* ========================================================================= */
struct TemplateArgument
{
    enum class Tag {
        Type,
        Number,
    };

    Tag tag;
    union {
        Type const *type;
        uint64_t number;
    };
};

class ClassTemplate : public Class
{
public:
    ClassTemplate(
        int size,
        uint64_t hash,
        Class *baseClass,
        Field *fields,
        Field *fieldsEnd,
        Function *functions,
        Function *functionsEnd,
        char const *name,
        size_t flags,
        TemplateArgument *templateArgs,
        TemplateArgument *templateArgsEnd) noexcept
    : Class(
        size,
        hash,
        baseClass,
        fields,
        fieldsEnd,
        functions,
        functionsEnd,
        name,
        flags)
    , m_templateArgs(templateArgs)
    , m_templateArgsEnd(templateArgsEnd)
    {}

public:
    TemplateArgument *m_templateArgs;
    TemplateArgument *m_templateArgsEnd;
};


/* ========================================================================= */
/* Detail                                                                    */
/* ========================================================================= */
namespace detail
{

template<class Type, size_t NFields, size_t NFunctions, size_t NTemplateArgs>
struct ClassStorage
{
    template<class Lambda>
    ClassStorage(Lambda &&ctor) noexcept
    {
        ctor(this);
    }

    size_t const numFields = NFields;
    size_t const numFunctions = NFunctions;
    size_t const numTemplateArgs = NTemplateArgs;
    /* Arrays of size 0 are UB. */
    Field fields[NFields + 1];
    Function functions[NFunctions + 1];
    TemplateArgument templateArgs[NTemplateArgs + 1];
};

} /* namespace detail */

} /* namespace metareflect */


/* ========================================================================= */
/* Primitives                                                                */
/* ========================================================================= */
#include "metareflect_fundamental.hxx"
#include "metareflect_templates.hxx"


/* ========================================================================= */
/* GetClass / GetType                                                        */
/* ========================================================================= */
namespace metareflect
{

template<class T>
inline Class const *
GetClass() noexcept
{
    return detail::GetClassImpl(ClassTag<T>{});
}

template<class T>
inline Type const *
GetType() noexcept
{
    return detail::GetTypeImpl(TypeTag<T>{});
}

} /* namespace metareflect */

#endif /* METAREFLECT_DETAIL_HXX */

