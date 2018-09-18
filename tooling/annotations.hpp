/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_ANNOTATIONS_HPP
#define METAREFLECT_ANNOTATIONS_HPP
#pragma once

#include "utils.hpp"

/* ========================================================================= */
/* Class Annotations                                                         */
/* ========================================================================= */
struct ClassAnnotations
{
    ClassAnnotations()
        : isSerializable(0)
        , hasBeforeSerialize(0)
        , hasAfterSerialize(0)
        , hasCustomSerialize(0)
        , hasCustomDump(0)
    {}

    bool isSerializable : 1;
    bool hasBeforeSerialize : 1;
    bool hasAfterSerialize : 1;
    bool hasCustomSerialize : 1;
    bool hasCustomDump : 1;

    struct FlagPrinter
    {
        ClassAnnotations const *annotations;

        explicit
        FlagPrinter(ClassAnnotations const *ref)
            : annotations(ref)
        {}
    };

    FlagPrinter
    Flags() const noexcept
    {
        return FlagPrinter{this};
    }
};

inline raw_ostream &
operator<<(raw_ostream &os, ClassAnnotations::FlagPrinter const &p)
{
    os << "Class::kFlagsNull";
    if (p.annotations->hasBeforeSerialize)
        os << " | Class::kFlagsHasBeforeSerialize";
    if (p.annotations->hasAfterSerialize)
        os << " | Class::kFlagsHasAfterSerialize";
    if (p.annotations->hasCustomSerialize)
        os << " | Class::kFlagsHasCustomSerialize";
    if (p.annotations->hasCustomDump)
        os << " | Class::kFlagsHasCustomDump";
    return os;
}


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
    bool isCString : 1;
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

    struct FlagPrinter
    {
        PropertyAnnotations const *annotations;

        explicit
        FlagPrinter(PropertyAnnotations const *ref)
            : annotations(ref)
        {}
    };

    FlagPrinter
    Flags() const noexcept
    {
        return FlagPrinter{this};
    }
};

inline raw_ostream &
operator<<(raw_ostream &os, PropertyAnnotations::FlagPrinter const &p)
{
    os << "Field::kFlagsNull";
    if (p.annotations->serialized)
        os << " | Field::kFlagsSerialized";
    if (p.annotations->isCString)
        os << " | Field::kFlagsCString";
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

    struct FlagPrinter
    {
        FunctionAnnotations const *annotations;

        explicit
        FlagPrinter(FunctionAnnotations const *ref)
            : annotations(ref)
        {}
    };

    FlagPrinter
    Flags() const noexcept
    {
        return FlagPrinter{this};
    }
};

inline raw_ostream &
operator<<(raw_ostream &os, FunctionAnnotations::FlagPrinter const &p)
{
    os << "Function::kFlagsNull";
    if (p.annotations->replicated)
        os << " | Function::kFlagsReplicated";
    if (p.annotations->memberFunc)
        os << " | Function::kFlagsMember";
    return os;
}


#endif /* METAREFLECT_ANNOTATIONS_HPP */

