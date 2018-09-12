/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<Point> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<Point> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<Point> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<Point> { static constexpr bool value = false; };

template<>
detail::ClassStorage<Point, 3, 1>::ClassStorage() noexcept
{

/* Field 1 */
fields[0].m_type = GetType<int>();
fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[0].m_serializedWidth = 32;
fields[0].m_offset = offsetof(Point, x);
fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[0].m_name = "x";

/* Field 2 */
fields[1].m_type = GetType<int>();
fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[1].m_serializedWidth = sizeof(int) * 8;
fields[1].m_offset = offsetof(Point, y);
fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[1].m_name = "y";

/* Field 3 */
fields[2].m_type = GetType<int>();
fields[2].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[2].m_serializedWidth = sizeof(int) * 8;
fields[2].m_offset = offsetof(Point, z);
fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[2].m_name = "z";

/* Function 1*/
static FunctionReturn functionRet0;
functionRet0.m_type = GetType<unsigned long>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(unsigned long) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static FunctionParameter functionParameters0[1];
functions[0].m_returnType = &functionRet0;
functions[0].m_parameters = &functionParameters0[0];
functions[0].m_parametersEnd = &functionParameters0[0];
functions[0].m_flags = Function::kFlagsNull | Function::kFlagsMember;
functions[0].m_name = "Hash";
}

template<>
Class const *
GetClass<Point>() noexcept
{
static detail::ClassStorage<Point, 3, 1> reflected;
static Class cache(
sizeof(Point),
Hash("Point"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"Point");
return &cache;
}

template<>
Type const *
GetType<Point>() noexcept
{
return GetClass<Point>();
}
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<RGBColor> { static constexpr bool value = false; };
template<> struct HasBeforeSerialize<RGBColor> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<RGBColor> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<RGBColor> { static constexpr bool value = false; };

template<>
detail::ClassStorage<RGBColor, 1, 0>::ClassStorage() noexcept
{

/* Field 1 */
fields[0].m_type = GetType<int>();
fields[0].m_flags = Field::kFlagsNull;
fields[0].m_serializedWidth = sizeof(int) * 8;
fields[0].m_offset = offsetof(RGBColor, rgb);
fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[0].m_name = "rgb";
}

template<>
Class const *
GetClass<RGBColor>() noexcept
{
static detail::ClassStorage<RGBColor, 1, 0> reflected;
static Class cache(
sizeof(RGBColor),
Hash("RGBColor"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"RGBColor");
return &cache;
}

template<>
Type const *
GetType<RGBColor>() noexcept
{
return GetClass<RGBColor>();
}
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<ColoredPoint> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<ColoredPoint> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<ColoredPoint> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<ColoredPoint> { static constexpr bool value = false; };

template<>
detail::ClassStorage<ColoredPoint, 2, 0>::ClassStorage() noexcept
{

/* Field 1 */
fields[0].m_type = GetType<Point>();
fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[0].m_serializedWidth = sizeof(Point) * 8;
fields[0].m_offset = offsetof(ColoredPoint, point);
fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[0].m_name = "point";

/* Field 2 */
fields[1].m_type = GetType<RGBColor>();
fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[1].m_serializedWidth = 24;
fields[1].m_offset = offsetof(ColoredPoint, color);
fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[1].m_name = "color";
}

template<>
Class const *
GetClass<ColoredPoint>() noexcept
{
static detail::ClassStorage<ColoredPoint, 2, 0> reflected;
static Class cache(
sizeof(ColoredPoint),
Hash("ColoredPoint"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"ColoredPoint");
return &cache;
}

template<>
Type const *
GetType<ColoredPoint>() noexcept
{
return GetClass<ColoredPoint>();
}
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<Object> { static constexpr bool value = false; };
template<> struct HasBeforeSerialize<Object> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<Object> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<Object> { static constexpr bool value = false; };

template<>
detail::ClassStorage<Object, 3, 0>::ClassStorage() noexcept
{

/* Field 1 */
fields[0].m_type = GetType<Point>();
fields[0].m_flags = Field::kFlagsNull;
fields[0].m_serializedWidth = sizeof(Point) * 8;
fields[0].m_offset = offsetof(Object, pPoint);
fields[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
fields[0].m_name = "pPoint";

/* Field 2 */
fields[1].m_type = GetType<Point>();
fields[1].m_flags = Field::kFlagsNull;
fields[1].m_serializedWidth = sizeof(Point) * 8;
fields[1].m_offset = offsetof(Object, points);
fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 1, 8);
fields[1].m_name = "points";

/* Field 3 */
fields[2].m_type = nullptr;
fields[2].m_flags = Field::kFlagsNull;
fields[2].m_serializedWidth = sizeof(Object) * 8;
fields[2].m_offset = offsetof(Object, children);
fields[2].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
fields[2].m_name = "children";
}

template<>
Class const *
GetClass<Object>() noexcept
{
static detail::ClassStorage<Object, 3, 0> reflected;
static Class cache(
sizeof(Object),
Hash("Object"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"Object");
return &cache;
}

template<>
Type const *
GetType<Object>() noexcept
{
return GetClass<Object>();
}
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<NPCObject> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<NPCObject> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<NPCObject> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<NPCObject> { static constexpr bool value = false; };

template<>
detail::ClassStorage<NPCObject, 1, 2>::ClassStorage() noexcept
{

/* Field 1 */
fields[0].m_type = GetType<Point>();
fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
fields[0].m_serializedWidth = sizeof(Point) * 8;
fields[0].m_offset = offsetof(NPCObject, position);
fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
fields[0].m_name = "position";

/* Function 1*/
static FunctionReturn functionRet0;
functionRet0.m_type = GetType<char>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(char) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
static FunctionParameter functionParameters0[1];
functions[0].m_returnType = &functionRet0;
functions[0].m_parameters = &functionParameters0[0];
functions[0].m_parametersEnd = &functionParameters0[0];
functions[0].m_flags = Function::kFlagsNull | Function::kFlagsMember;
functions[0].m_name = "GetName";

/* Function 2*/
static FunctionReturn functionRet1;
functionRet1.m_type = GetType<void>();
functionRet1.m_flags = 0/*TODO*/;
functionRet1.m_serializedWidth = 0 * 8;
functionRet1.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static FunctionParameter functionParameters1[1];
functionParameters1[0].m_type = GetType<char>();
functionParameters1[0].m_flags = 0/*TODO*/;
functionParameters1[0].m_serializedWidth = sizeof(char) * 8;
functionParameters1[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters1[0].m_name = "name";
functions[1].m_returnType = &functionRet1;
functions[1].m_parameters = &functionParameters1[0];
functions[1].m_parametersEnd = &functionParameters1[1];
functions[1].m_flags = Function::kFlagsNull | Function::kFlagsMember;
functions[1].m_name = "SetName";
}

template<>
Class const *
GetClass<NPCObject>() noexcept
{
static detail::ClassStorage<NPCObject, 1, 2> reflected;
static Class cache(
sizeof(NPCObject),
Hash("NPCObject"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"NPCObject");
return &cache;
}

template<>
Type const *
GetType<NPCObject>() noexcept
{
return GetClass<NPCObject>();
}
} /* namespace metareflect */

