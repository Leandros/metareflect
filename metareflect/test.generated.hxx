/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<Point> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<Point> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<Point> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<Point> { static constexpr bool value = false; };
template<> struct HasCustomDump<Point> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<Point>) noexcept
{
static detail::ClassStorage<Point, 3, 1> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<int>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = 32;
self->fields[0].m_offset = offsetof(Point, x);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "x";

/* Field 2 */
self->fields[1].m_type = GetType<int>();
self->fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(int) * 8;
self->fields[1].m_offset = offsetof(Point, y);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "y";

/* Field 3 */
self->fields[2].m_type = GetType<unsigned long>();
self->fields[2].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[2].m_serializedWidth = sizeof(unsigned long) * 8;
self->fields[2].m_offset = offsetof(Point, z);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[2].m_name = "z";

/* Function 1*/
static FunctionReturn functionRet0;
functionRet0.m_type = GetType<unsigned long>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(unsigned long) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static FunctionParameter functionParameters0[1];
self->functions[0].m_returnType = &functionRet0;
self->functions[0].m_parameters = &functionParameters0[0];
self->functions[0].m_parametersEnd = &functionParameters0[0];
self->functions[0].m_flags = Function::kFlagsNull | Function::kFlagsMember;
self->functions[0].m_name = "Hash";
});
static Class cache(
sizeof(Point),
Hash("Point"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"Point",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<Point>) noexcept
{
return GetClass<Point>();
}
} /* namespace detail */
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<RGBColor> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<RGBColor> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<RGBColor> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<RGBColor> { static constexpr bool value = false; };
template<> struct HasCustomDump<RGBColor> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<RGBColor>) noexcept
{
static detail::ClassStorage<RGBColor, 1, 0> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<unsigned int>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(unsigned int) * 8;
self->fields[0].m_offset = offsetof(RGBColor, rgb);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "rgb";
});
static Class cache(
sizeof(RGBColor),
Hash("RGBColor"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"RGBColor",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<RGBColor>) noexcept
{
return GetClass<RGBColor>();
}
} /* namespace detail */
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
template<> struct HasCustomDump<ColoredPoint> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<ColoredPoint>) noexcept
{
static detail::ClassStorage<ColoredPoint, 3, 0> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<Point>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(Point) * 8;
self->fields[0].m_offset = offsetof(ColoredPoint, point);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "point";

/* Field 2 */
self->fields[1].m_type = GetType<RGBColor>();
self->fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[1].m_serializedWidth = 24;
self->fields[1].m_offset = offsetof(ColoredPoint, color);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "color";

/* Field 3 */
self->fields[2].m_type = GetType<char>();
self->fields[2].m_flags = Field::kFlagsNull | Field::kFlagsSerialized | Field::kFlagsCString;
self->fields[2].m_serializedWidth = sizeof(char) * 8;
self->fields[2].m_offset = offsetof(ColoredPoint, name);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[2].m_name = "name";
});
static Class cache(
sizeof(ColoredPoint),
Hash("ColoredPoint"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"ColoredPoint",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<ColoredPoint>) noexcept
{
return GetClass<ColoredPoint>();
}
} /* namespace detail */
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<Object> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<Object> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<Object> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<Object> { static constexpr bool value = false; };
template<> struct HasCustomDump<Object> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<Object>) noexcept
{
static detail::ClassStorage<Object, 4, 0> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<Point>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(Point) * 8;
self->fields[0].m_offset = offsetof(Object, pPoint);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[0].m_name = "pPoint";

/* Field 2 */
self->fields[1].m_type = GetType<Point>();
self->fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(Point) * 8;
self->fields[1].m_offset = offsetof(Object, points);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 1, 3);
self->fields[1].m_name = "points";

/* Field 3 */
self->fields[2].m_type = nullptr;
self->fields[2].m_flags = Field::kFlagsNull;
self->fields[2].m_serializedWidth = sizeof(Object) * 8;
self->fields[2].m_offset = offsetof(Object, children);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[2].m_name = "children";

/* Field 4 */
self->fields[3].m_type = nullptr;
self->fields[3].m_flags = Field::kFlagsNull;
self->fields[3].m_serializedWidth = sizeof(Object) * 8;
self->fields[3].m_offset = offsetof(Object, parent);
self->fields[3].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[3].m_name = "parent";
});
static Class cache(
sizeof(Object),
Hash("Object"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"Object",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<Object>) noexcept
{
return GetClass<Object>();
}
} /* namespace detail */
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
template<> struct HasCustomDump<NPCObject> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<NPCObject>) noexcept
{
static detail::ClassStorage<NPCObject, 1, 2> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<Point>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(Point) * 8;
self->fields[0].m_offset = offsetof(NPCObject, position);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "position";

/* Function 1*/
static FunctionReturn functionRet0;
functionRet0.m_type = GetType<char>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(char) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
static FunctionParameter functionParameters0[1];
self->functions[0].m_returnType = &functionRet0;
self->functions[0].m_parameters = &functionParameters0[0];
self->functions[0].m_parametersEnd = &functionParameters0[0];
self->functions[0].m_flags = Function::kFlagsNull | Function::kFlagsMember;
self->functions[0].m_name = "GetName";

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
self->functions[1].m_returnType = &functionRet1;
self->functions[1].m_parameters = &functionParameters1[0];
self->functions[1].m_parametersEnd = &functionParameters1[1];
self->functions[1].m_flags = Function::kFlagsNull | Function::kFlagsMember;
self->functions[1].m_name = "SetName";
});
static Class cache(
sizeof(NPCObject),
Hash("NPCObject"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"NPCObject",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<NPCObject>) noexcept
{
return GetClass<NPCObject>();
}
} /* namespace detail */
} /* namespace metareflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "metareflect.hxx"
namespace metareflect
{

template<> struct IsSerializable<User> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<User> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<User> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<User> { static constexpr bool value = false; };
template<> struct HasCustomDump<User> { static constexpr bool value = false; };
namespace detail
{
template<>
Class const *
GetClassImpl(ClassTag<User>) noexcept
{
static detail::ClassStorage<User, 3, 0> reflected([](auto self) {

/* Field 1 */
self->fields[0].m_type = GetType<unsigned long long>();
self->fields[0].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(unsigned long long) * 8;
self->fields[0].m_offset = offsetof(User, id);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "id";

/* Field 2 */
self->fields[1].m_type = GetType<std::__1::basic_string<char>>();
self->fields[1].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(std::__1::basic_string<char>) * 8;
self->fields[1].m_offset = offsetof(User, name);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "name";

/* Field 3 */
self->fields[2].m_type = GetType<std::__1::vector<std::__1::basic_string<char>, std::__1::allocator<std::__1::basic_string<char> > >>();
self->fields[2].m_flags = Field::kFlagsNull | Field::kFlagsSerialized;
self->fields[2].m_serializedWidth = sizeof(std::__1::vector<std::__1::basic_string<char>, std::__1::allocator<std::__1::basic_string<char> > >) * 8;
self->fields[2].m_offset = offsetof(User, pets);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[2].m_name = "pets";
});
static Class cache(
sizeof(User),
Hash("User"),
nullptr/*TODO: baseclass*/,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"User",
Class::kFlagsNull);
return &cache;
}

template<>
Type const *
GetTypeImpl(TypeTag<User>) noexcept
{
return GetClass<User>();
}
} /* namespace detail */
} /* namespace metareflect */

