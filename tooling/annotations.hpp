/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_ANNOTATIONS_HPP
#define METAREFLECT_ANNOTATIONS_HPP
#pragma once

#include "utils.hpp"

/* ========================================================================= */
/* Property Annotations                                                      */
/* ========================================================================= */
struct PropertyAnnotations
{
    PropertyAnnotations()
        : serialized(false)
        , width(0)
    {}

    bool serialized : 1;
    unsigned width : 8;

    bool
    IsSerializable(
        ASTContext *ctx,
        FieldDecl const *field)
    {
        auto t = GetDesugaredType(ctx, field->getType());
        if (!t.isPODType(*ctx) && serialized)
            return false;
        return true;
    }

    struct PropertyFlagsPrinter
    {
        PropertyAnnotations const *annotations;

        explicit
        PropertyFlagsPrinter(PropertyAnnotations const *ref)
            : annotations(ref)
        {}
    };

    PropertyFlagsPrinter
    Flags() const noexcept
    {
        return PropertyFlagsPrinter{this};
    }
};

inline raw_ostream &
operator<<(raw_ostream &os, PropertyAnnotations::PropertyFlagsPrinter const &p)
{
    os << "Field::kFlagsNull";
    if (p.annotations->serialized)
        os << " | Field::kFlagsSerialized";
    return os;
}


/* ========================================================================= */
/* Function Annotations                                                      */
/* ========================================================================= */
struct FunctionAnnotations
{
    FunctionAnnotations()
        : replicated(false)
        , memberFunc(false)
    {}

    bool replicated : 1;
    bool memberFunc : 1;

    struct FunctionFlagsPrinter
    {
        FunctionAnnotations const *annotations;

        explicit
        FunctionFlagsPrinter(FunctionAnnotations const *ref)
            : annotations(ref)
        {}
    };

    FunctionFlagsPrinter
    Flags() const noexcept
    {
        return FunctionFlagsPrinter{this};
    }
};

inline raw_ostream &
operator<<(raw_ostream &os, FunctionAnnotations::FunctionFlagsPrinter const &p)
{
    os << "Function::kFlagsNull";
    if (p.annotations->replicated)
        os << " | Function::kFlagsReplicated";
    if (p.annotations->memberFunc)
        os << " | Function::kFlagsMember";
    return os;
}


#endif /* METAREFLECT_ANNOTATIONS_HPP */

