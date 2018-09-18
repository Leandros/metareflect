/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_FIELD_GENERATOR_HPP
#define METAREFLECT_FIELD_GENERATOR_HPP
#pragma once

#include "utils.hpp"
#include "annotations.hpp"


inline raw_ostream &
operator<<(raw_ostream &os, PropertyAnnotations &p)
{
    return os;
}


/* ========================================================================= */
/* Field Generator                                                           */
/* ========================================================================= */
struct FieldGenerator
{
    ASTContext * const ctx;
    SmallString<64> fieldName;
    SmallString<64> typeName;
    raw_svector_ostream fieldNameOs{fieldName};
    raw_svector_ostream TypeNameOs{typeName};
    StringRef const type;
    std::string const fieldPrefix;

    explicit
    FieldGenerator(
        ASTContext *context,
        StringRef const &parentType,
        StringRef const &prefix)
        : ctx(context)
        , type(parentType)
        , fieldPrefix(prefix)
    {}

    void
    Generate(
        unsigned i,
        FieldDecl const *field,
        PropertyAnnotations &annotations,
        raw_ostream &os)
    {
        fieldName.clear();
        typeName.clear();

        field->printName(fieldNameOs);
        GetRealTypeName(ctx, field->getType(), TypeNameOs);

        auto prefix = [&]() -> raw_ostream & {
            return os << fieldPrefix << "[" << i << "]";
        };

        bool isSerializable = annotations.IsSerializable(ctx, field);
        unsigned serializedWidth = annotations.width;

        os << "\n/* Field " << (i + 1) << " */\n";
        if (type != typeName)
            /* prefix() << ".m_type = TypeResolver<" << typeName << ">::Get();\n"; */
            prefix() << ".m_type = GetType<" << typeName << ">();\n";
        else
            prefix() << ".m_type = nullptr;\n";
        prefix() << ".m_flags = " << annotations.Flags() << ";\n";
        if (isSerializable && serializedWidth > 0)
            prefix() << ".m_serializedWidth = " << serializedWidth << ";\n";
        else
            prefix() << ".m_serializedWidth = sizeof(" << typeName << ") * 8;\n";
        prefix() << ".m_offset = offsetof(" << type << ", " << fieldName << ");\n";
        prefix() << ".m_qualifier = " << GenerateQualifier(ctx, field->getType()) << ";\n";
        prefix() << ".m_name = \"" << fieldName << "\";\n";
    }
};

#endif /* METAREFLECT_FIELD_GENERATOR_HPP */
