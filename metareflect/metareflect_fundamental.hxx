/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */


/* ===-------------------------------------------------------------------=== */
/* Fundamental Type Access                                                   */
/* ===-------------------------------------------------------------------=== */
#define TYPES                                       \
    X(bool, Bool, "%d")                             \
    X(char, Char, "%d")                             \
    X(short, Short, "%d")                           \
    X(int, Int, "%d")                               \
    X(long, Long, "%ld")                            \
    X(long long, LongLong, "%lld")                  \
    X(float, Float, "%.9g")                         \
    X(double, Double, "%.17g")                      \
    X(long double, LongDouble, "%.21Lg")            \
    X(unsigned char, UnsignedChar, "%u")            \
    X(unsigned short, UnsignedShort, "%u")          \
    X(unsigned int, UnsignedInt, "%u")              \
    X(unsigned long, UnsignedLong, "%lu")           \
    X(unsigned long long, UnsignedLongLong, "%llu") \

#define XSTRINGIFY(s) #s
#define STRINGIFY(s) XSTRINGIFY(s)

namespace metareflect
{
namespace detail
{

#ifdef FUNDAMENTAL_IMPL
#undef FUNDAMENTAL_IMPL

#define X(T, NAME, FMT) \
Type const * \
GetTypeImpl(TypeTag<T>) noexcept \
{ \
    struct NAME : public Type { \
        using Type::Type; \
        virtual void \
        Dump(void const *instance, FILE *file = stdout) const noexcept \
        { \
            fprintf(file, FMT, *(T const *)instance); \
        } \
    }; \
    static NAME type{ sizeof(T), Hash(STRINGIFY(T)), STRINGIFY(T), }; \
    return &type; \
}

/* void is special. */
Type const *
GetTypeImpl(TypeTag<void>) noexcept
{
    struct Void : public Type {
        using Type::Type;
        virtual void
        Dump(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "%p", instance);
        }
    };
    static Void type{ 0, Hash("void"), "void" };
    return &type;
}

#else /* ifdef FUNDAMENTAL_IMPL */

#define X(T, NAME, FMT) \
    extern Type const *GetTypeImpl(TypeTag<T>) noexcept;
extern Type const *GetTypeImpl(TypeTag<void>) noexcept;

#endif /* ifndef FUNDAMENTAL_IMPL */

TYPES

#undef X

} /* namespace detail */
} /* namespace metareflect */

