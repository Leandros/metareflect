/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */


/* ===-------------------------------------------------------------------=== */
/* Fundamental Type Access                                                   */
/* ===-------------------------------------------------------------------=== */
template<>
Type const *
GetType<void>() noexcept
{
    static Type type{0, Hash("void")};
    return &type;
}

template<>
Type const *
GetType<bool>() noexcept
{
    static Type type{sizeof(bool), Hash("bool")};
    return &type;
}

template<>
Type const *
GetType<signed char>() noexcept
{
    static Type type{sizeof(signed char), Hash("signed char")};
    return &type;
}

template<>
Type const *
GetType<unsigned char>() noexcept
{
    static Type type{sizeof(unsigned char), Hash("unsigned char")};
    return &type;
}

template<>
Type const *
GetType<signed short>() noexcept
{
    static Type type{sizeof(signed short), Hash("signed short")};
    return &type;
}

template<>
Type const *
GetType<unsigned short>() noexcept
{
    static Type type{sizeof(unsigned short), Hash("unsigned short")};
    return &type;
}

template<>
Type const *
GetType<signed int>() noexcept
{
    static Type type{sizeof(signed int), Hash("signed int")};
    return &type;
}

template<>
Type const *
GetType<unsigned int>() noexcept
{
    static Type type{sizeof(unsigned int), Hash("unsigned int")};
    return &type;
}

template<>
Type const *
GetType<signed long>() noexcept
{
    static Type type{sizeof(signed long), Hash("signed long")};
    return &type;
}

template<>
Type const *
GetType<unsigned long>() noexcept
{
    static Type type{sizeof(unsigned long), Hash("unsigned long")};
    return &type;
}

template<>
Type const *
GetType<signed long long>() noexcept
{
    static Type type{sizeof(signed long long), Hash("signed long long")};
    return &type;
}

template<>
Type const *
GetType<unsigned long long>() noexcept
{
    static Type type{sizeof(unsigned long long), Hash("unsigned long long")};
    return &type;
}

template<>
Type const *
GetType<float>() noexcept
{
    static Type type{sizeof(float), Hash("float")};
    return &type;
}

template<>
Type const *
GetType<double>() noexcept
{
    static Type type{sizeof(double), Hash("double")};
    return &type;
}

template<>
Type const *
GetType<long double>() noexcept
{
    static Type type{sizeof(long double), Hash("long double")};
    return &type;
}

