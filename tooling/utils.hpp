/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_UTILS_HPP
#define METAREFLECT_UTILS_HPP
#pragma once

#include <string>
#include <algorithm>

/* -- LLVM includes */
#include "clang/Frontend/FrontendActions.h"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include "clang/AST/RecursiveASTVisitor.h"

/* Declares llvm::cl::extrahelp. */
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;


/* ========================================================================= */
/* STL Utils                                                                 */
/* ========================================================================= */
inline bool
ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size())
        return false;

    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

/* ========================================================================= */
/* LLVM Utils                                                                */
/* ========================================================================= */
QualType
GetDesugaredType(ASTContext *ctx, QualType t);

inline void
GetRealTypeName(ASTContext *ctx, QualType t, raw_ostream &os)
{
    QualType retType = GetDesugaredType(ctx, t);
    retType.print(os, ctx->getPrintingPolicy());
}

SmallString<32>
GenerateQualifier(ASTContext *ctx, QualType type);

#endif /* METAREFLECT_UTILS_HPP */

