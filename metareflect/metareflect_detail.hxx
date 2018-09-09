/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */
#ifndef METAREFLECT_DETAIL_HXX
#define METAREFLECT_DETAIL_HXX
#pragma once

/* Forward declare storages, for friend declarations. */
namespace detail
{

template<size_t NFields, size_t NFunctions>
struct ClassStorage;

template<size_t NParameter>
struct FunctionStorage;

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

private:
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
        : arrayCount(count)
        , cvQualifier(cv)
        , refQualifier(ref)
        , storageClass(storage)
        , isPointer(pointer)
        , isArray(array)
    {}

    unsigned arrayCount;
    unsigned char cvQualifier : 3;
    unsigned char refQualifier : 3;
    unsigned char storageClass : 3;
    unsigned char isPointer : 1;
    unsigned char isArray : 1;
};


/* ===-------------------------------------------------------------------=== */
/* Primitive Types                                                           */
/* ===-------------------------------------------------------------------=== */
/* Everything derives from primitive. */
class Primitive {};


/* ===-------------------------------------------------------------------=== */
/* Type                                                                      */
/* ===-------------------------------------------------------------------=== */
/* All types inherit from 'Type' */
class Type : public Primitive
{
    template<size_t N, size_t J>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    Type() noexcept
        : m_size(0)
        , m_hash(0)
    {}

    Type(int size, uint64_t hash) noexcept
        : m_size(size)
        , m_hash(hash)
    {}


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


private:
    uint64_t m_size;
    uint64_t m_hash;
};


/* ===-------------------------------------------------------------------=== */
/* Field                                                                     */
/* ===-------------------------------------------------------------------=== */
/* All fields of classes are represented via this class. */
class Field : public Primitive
{
    template<size_t N, size_t J>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    static constexpr unsigned kFlagsNull       = 0x0;
    static constexpr unsigned kFlagsSerialized = 0x1;

    Field() noexcept = default;

    Field(
        Type *type,
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
    /* Access                                                                */
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

private:
    metareflect::Type *m_type;
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
    template<size_t N, size_t J>
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
    template<size_t N, size_t J>
    friend struct detail::ClassStorage;
    template<size_t N>
    friend struct detail::FunctionStorage;

public:
    /* Inherit constructor. */
    using Field::Field;
};


/* ====== Function ====== */
class Function : public Primitive
{
    template<size_t N, size_t J>
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
    /* Access                                                                */
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

private:
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
        Function *functionsEnd) noexcept
        : Type(size, hash)
        , m_baseClass(baseClass)
        , m_fields(fields)
        , m_fieldsEnd(fieldsEnd)
        , m_functions(functions)
        , m_functionsEnd(functionsEnd)
    {}


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


private:
    Class *m_baseClass;
    Field *m_fields;
    Field *m_fieldsEnd;
    Function *m_functions;
    Function *m_functionsEnd;
};


/* ========================================================================= */
/* Detail                                                                    */
/* ========================================================================= */
namespace detail
{

template<size_t NFields, size_t NFunctions>
struct ClassStorage
{
    static_assert(NFields > 0 || NFunctions > 0 ,
        "may not reflect empty classes");
    ClassStorage() noexcept;
    size_t numFields = NFields;
    size_t numFunctions = NFunctions;
    /* Arrays of size 0 are UB. */
    Field fields[NFields > 0 ? NFields : 1];
    /* Arrays of size 0 are UB. */
    Function functions[NFunctions > 0 ? NFunctions : 1];
};

template<size_t NParameter>
struct FunctionStorage
{
    static_assert(NParameter > 0, "Void is a parameter, too!");

    FunctionStorage() noexcept;
    size_t numParameter = NParameter;
    Field returnValue;
    Field parameter[NParameter];
};

} /* namespace detail */

#endif /* METAREFLECT_DETAIL_HXX */

