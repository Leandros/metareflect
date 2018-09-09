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
GetType<char>() noexcept
{
    static Type type{sizeof(char), Hash("char")};
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
GetType<short>() noexcept
{
    static Type type{sizeof(short), Hash("short")};
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
GetType<int>() noexcept
{
    static Type type{sizeof(int), Hash("int")};
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
GetType<long>() noexcept
{
    static Type type{sizeof(long), Hash("long")};
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
GetType<long long>() noexcept
{
    static Type type{sizeof(long long), Hash("long long")};
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

