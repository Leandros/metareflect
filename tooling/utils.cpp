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
        /* TODO: How to handle non-constant arrays? */
        clang::ArrayType const *arr = t->getAsArrayTypeUnsafe();
        if (arr->isConstantSizeType()) {
            assert(arr != nullptr && "arr is null");
            auto carr = (clang::ConstantArrayType const *)arr;
            auto size = carr->getSize();
            arrayLen = *size.getRawData();
        }
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

SmallString<8>
PrintfFormatForType(ASTContext *ctx, QualType t)
{
    QualType desugared = GetDesugaredType(ctx, t);
    clang::Type const *type = desugared.getTypePtrOrNull();
    if (type == nullptr) {
        printf("TODO: TYPE IS NULLPTR\n");
        return SmallString<8>("");
    }

    bool isFundamental = type->isFundamentalType();
    printf("isFundamental: %d\n", isFundamental);
    if (isFundamental) {
        clang::BuiltinType const *builtin = type->getAs<BuiltinType>();
        switch (builtin->getKind()) {
        case BuiltinType::Kind::Bool:
        case BuiltinType::Kind::SChar:
        case BuiltinType::Kind::Short:
        case BuiltinType::Kind::Int:
            return SmallString<8>("%d");
        case BuiltinType::Kind::UChar:
        case BuiltinType::Kind::UShort:
        case BuiltinType::Kind::UInt:
            return SmallString<8>("%u");
        case BuiltinType::Kind::Long:
            return SmallString<8>("%ld");
        case BuiltinType::Kind::ULong:
            return SmallString<8>("%lu");
        case BuiltinType::Kind::LongLong:
            return SmallString<8>("%lld");
        case BuiltinType::Kind::ULongLong:
            return SmallString<8>("%llu");
        case BuiltinType::Kind::Float:
        case BuiltinType::Kind::Double:
        case BuiltinType::Kind::LongDouble:
            return SmallString<8>("%f");
        default:
            break;
        }
    }

    return SmallString<8>("");
}

