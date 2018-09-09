/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#include "utils.hpp"

struct TypeVisitor : public RecursiveASTVisitor<TypeVisitor>
{
    explicit TypeVisitor(ASTContext *context)
        : m_context(context)
    {}

    bool
    VisitType(clang::Type *type)
    {
        m_leaf = type;
        return true;
    }

    ASTContext *m_context;
    clang::Type *m_leaf;
};

QualType
GetDesugaredType(ASTContext *ctx, QualType t)
{
    TypeVisitor v{ ctx };
    v.TraverseType(t);
    clang::Type const *type = v.m_leaf->getUnqualifiedDesugaredType();
    QualType retType(type, 0);
    return retType;
}

SmallString<32>
GenerateQualifier(ASTContext *ctx, QualType type)
{
    clang::Type const *t = type.getTypePtrOrNull();

    /* CV Qualifier: */
    int cvQual = 0;
    if (type.isConstant(*ctx))
        cvQual |= 0x1;

    if (type.isVolatileQualified())
        cvQual |= 0x2;

    /* RefQualifier: */
    int refQual = 0;
    if (t->isLValueReferenceType())
        refQual = 1;

    if (t->isRValueReferenceType())
        refQual = 2;

    /* StorageClass: */
    int storageClass = 0;
    /* TODO: Implement! */

    /* Pointer detection: */
    int isPointer = t->isPointerType();

    /* Array detection: */
    int isArray = t->isArrayType();
    int arrayLen = 0;
    if (isArray) {
        /* TODO Implement! */
        /* clang::ArrayType const *arr = t->getAsArrayTypeUnsafe(); */
    }

    SmallString<32> out;
    raw_svector_ostream os(out);
    os << "Qualifier("
       << cvQual << ", "
       << refQual << ", "
       << storageClass << ", "
       << isPointer << ", "
       << isArray << ", "
       << arrayLen << ")";
    return out;
}

