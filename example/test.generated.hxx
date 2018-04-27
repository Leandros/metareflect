/* this file is generated. do not edit! */
#pragma once

#include "metareflect.hxx"

#if 1
namespace metareflect
{

template<> struct IsSerializable<Point> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<Point> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<Point> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<Point> { static constexpr bool value = false; };

template<>
detail::ClassStorage<3, 1>::ClassStorage() noexcept
{
    /* Field 1 */
    static Type type0{sizeof(int), Hash("signed int")};
    fields[0].m_type = &type0;
    fields[0].m_flags = Field::kFlagsSerialized;
    fields[0].m_serializedWidth = 32;
    fields[0].m_offset = offsetof(::Point, x);
    fields[0].m_qualifier = Qualifier{kCVQualifierNone, kRefQualifierNone, kStorageClassMember};

    /* Field 2 */
    static Type type1{sizeof(int), Hash("signed int")};
    fields[1].m_type = &type1;
    fields[1].m_flags = Field::kFlagsSerialized;
    fields[1].m_serializedWidth = 32;
    fields[1].m_offset = offsetof(::Point, y);
    fields[1].m_qualifier = Qualifier{kCVQualifierNone, kRefQualifierNone, kStorageClassMember};

    /* Field 3 */
    static Type type2{sizeof(int), Hash("signed int")};
    fields[2].m_type = &type2;
    fields[2].m_flags = Field::kFlagsSerialized;
    fields[2].m_serializedWidth = 32;
    fields[2].m_offset = offsetof(::Point, z);
    fields[2].m_qualifier = Qualifier{kCVQualifierNone, kRefQualifierNone, kStorageClassMember};

    /* Function 1 */
    static Type functionRetType0{sizeof(unsigned long long), Hash("unsigned long long")};
    static FunctionReturn functionRet0;
    functionRet0.m_type = &functionRetType0;
    functionRet0.m_flags = Field::kFlagsNull;
    functionRet0.m_serializedWidth = 0;
    functionRet0.m_qualifier = Qualifier{};

    static FunctionParameter functionParameters0[1];
    static Type functionParameterType00{sizeof(::Point), Hash("::Point")};
    functionParameters0[0].m_type = &functionParameterType00;
    functionParameters0[0].m_flags = Field::kFlagsNull;
    functionParameters0[0].m_serializedWidth = 0;
    functionParameters0[0].m_qualifier = Qualifier{kCVQualifierConst, kRefQualifierNone, kStorageClassMember, true};

    functions[0].m_returnType = &functionRet0;
    functions[0].m_parameters = &functionParameters0[0];
    functions[0].m_parametersEnd = &functionParameters0[1];
    functions[0].m_flags = Function::kFlagsNull;
}

template<>
Class const *
GetClass<Point>() noexcept
{
    static detail::ClassStorage<3, 1> reflected;
    static Class cache{
        sizeof(::Point),
        Hash("::Point"),
        nullptr,
        reflected.fields,
        reflected.fields + reflected.numFields,
        reflected.functions,
        reflected.functions + reflected.numFunctions};

    return &cache;
}

template<>
Type const *
GetType<Point>() noexcept
{
    return GetClass<Point>();
}

template<class Serializer>
struct Serialize<Point, Serializer>
{
    constexpr bool
    operator()(Point &obj, Serializer &serializer) noexcept
    {
        serializer.SerializeBits(obj.x, 32);
        serializer.SerializeBits(obj.y, 32);
        serializer.SerializeBits(obj.z, 32);
        if constexpr (HasCustomSerialize<Point>::value)
            if (!obj.Serialize(serializer))
                return false;
        return true;
    }
};

} /* namespace metareflect */

#endif /* if 0 */
