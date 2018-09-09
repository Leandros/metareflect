/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_REFLECTED_CLASS_HPP
#define METAREFLECT_REFLECTED_CLASS_HPP
#pragma once

#include "utils.hpp"
#include "annotations.hpp"


class ReflectedClass
{
public:
    ReflectedClass(CXXRecordDecl const *rec)
        : m_record(rec)
    {}

    /* ===--------------------------------------------------=== */
    /* Public API                                               */
    /* ===--------------------------------------------------=== */
    void
    Generate(ASTContext *ctx, raw_ostream &os);

    void
    AddField(FieldDecl const *field)
    {
        m_fields.push_back(field);
    }

    void
    AddFunction(FunctionDecl const *function)
    {
        m_functions.push_back(function);
    }


    /* ===--------------------------------------------------=== */
    /* Generate Annotations                                     */
    /* ===--------------------------------------------------=== */
    PropertyAnnotations
    GenerateFieldAttributes(StringRef const &attr);

    FunctionAnnotations
    GenerateFunctionAttributes(StringRef const &attr);


    /* ===--------------------------------------------------=== */
    /* Helper                                                   */
    /* ===--------------------------------------------------=== */
private:
    template<class T>
    Attr *
    GetAnnotateAttr(T *decl)
    {
        for (auto &attr : decl->attrs()) {
            if (attr->getKind() == attr::Annotate) {
                return attr;
            }
        }

        return nullptr;
    }

    template<unsigned N>
    StringRef
    GetAnnotations(Attr const *attr, SmallString<N> &str)
    {
        str.clear();
        raw_svector_ostream os(str);
        LangOptions langopts;
        PrintingPolicy policy(langopts);
        attr->printPretty(os, policy);
        return str.slice(26, str.size() - 4);
    }

    template<class Lambda>
    bool
    ForEachProperty(StringRef const &annotations, Lambda &&lambda)
    {
        auto pair = annotations.split(',');
        if (pair.first.size() == 0)
            return true;
        if (!lambda(pair.first.trim()))
            return false;
        return ForEachProperty(pair.second, static_cast<Lambda &&>(lambda));
    }

    bool
    HasFunctionOfName(char const *name)
    {
        SmallString<64> str;
        return std::any_of(
            m_functions.begin(),
            m_functions.end(),
            [&str, &name](FunctionDecl const *&v) {
                str.clear();
                raw_svector_ostream fos(str);
                v->printName(fos);
                return str == name;
            });
    }

private:
    CXXRecordDecl const * const m_record;
    std::vector<FieldDecl const *> m_fields;
    std::vector<FunctionDecl const *> m_functions;
};

#endif /* METAREFLECT_REFLECTED_CLASS_HPP */

