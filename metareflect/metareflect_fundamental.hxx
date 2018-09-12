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
    struct Void : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "void{%p}", instance);
        }
    };
    static Void type{ 0, Hash("void"), "void" };
    return &type;
}

template<>
Type const *
GetType<bool>() noexcept
{
    struct Bool : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "bool{%d}", *(bool const *)instance);
        }
    };
    static Bool type{ sizeof(bool), Hash("bool"), "bool", };
    return &type;
}

template<>
Type const *
GetType<char>() noexcept
{
    struct Char : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "char{%d}", *(char const *)instance);
        }
    };
    static Char type{ sizeof(char), Hash("char"), "char", };
    return &type;
}

template<>
Type const *
GetType<unsigned char>() noexcept
{
    struct UChar : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "unsigned char{%u}", *(unsigned char const *)instance);
        }
    };
    static UChar type{
        sizeof(unsigned char),
        Hash("unsigned char"),
        "unsigned char",
    };
    return &type;
}

template<>
Type const *
GetType<short>() noexcept
{
    struct Short : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "short{%d}", *(short const *)instance);
        }
    };
    static Short type{ sizeof(short), Hash("short"), "short", };
    return &type;
}

template<>
Type const *
GetType<unsigned short>() noexcept
{
    struct UShort : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "unsigned short{%u}", *(unsigned short const *)instance);
        }
    };
    static UShort type{
        sizeof(unsigned short),
        Hash("unsigned short"),
        "unsigned short",
    };
    return &type;
}

template<>
Type const *
GetType<int>() noexcept
{
    struct Int : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "int{%d}", *(int const *)instance);
        }
    };
    static Int type{ sizeof(int), Hash("int"), "int", };
    return &type;
}

template<>
Type const *
GetType<unsigned int>() noexcept
{
    struct UInt : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "unsigned int{%u}", *(unsigned int const *)instance);
        }
    };
    static UInt type{
        sizeof(unsigned int),
        Hash("unsigned int"),
        "unsigned int",
    };
    return &type;
}

template<>
Type const *
GetType<long>() noexcept
{
    struct Long : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "long{%ld}", *(long const *)instance);
        }
    };
    static Long type{ sizeof(long), Hash("long"), "long", };
    return &type;
}

template<>
Type const *
GetType<unsigned long>() noexcept
{
    struct ULong : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "unsigned long{%lu}", *(unsigned long const *)instance);
        }
    };
    static ULong type{
        sizeof(unsigned long),
        Hash("unsigned long"),
        "unsigned long",
    };
    return &type;
}

template<>
Type const *
GetType<long long>() noexcept
{
    struct LongLong : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "long long{%lld}", *(long long const *)instance);
        }
    };
    static LongLong type{ sizeof(long long), Hash("long long"), "long long", };
    return &type;
}

template<>
Type const *
GetType<unsigned long long>() noexcept
{
    struct ULongLong : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "unsigned long long{%llu}", *(unsigned long long const *)instance);
        }
    };
    static ULongLong type{
        sizeof(unsigned long long),
        Hash("unsigned long long"),
        "unsigned long long",
    };
    return &type;
}

template<>
Type const *
GetType<float>() noexcept
{
    struct Float : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "float{%.9g}", *(float const *)instance);
        }
    };
    static Float type{ sizeof(float), Hash("float"), "float", };
    return &type;
}

template<>
Type const *
GetType<double>() noexcept
{
    struct Double : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "double{%.17g}", *(double const *)instance);
        }
    };
    static Double type{ sizeof(double), Hash("double"), "double", };
    return &type;
}

template<>
Type const *
GetType<long double>() noexcept
{
    struct LongDouble : public Type {
        using Type::Type;
        virtual void
        Print(void const *instance, FILE *file = stdout) const noexcept
        {
            fprintf(file, "long double{%.21Lg}", *(long double const *)instance);
        }
    };
    static LongDouble type{ sizeof(long double), Hash("long double"), "long double", };
    return &type;
}

