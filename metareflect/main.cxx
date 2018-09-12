#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <type_traits>
#include <memory>
#include "test.hxx"

char const *spaces =
"                                                                             "
"                                                                             "
"                                                                             ";

/* TODO TODO TODO
 * Add std::vector & std::unordered_map to the "primitive" types.
 * Add a new "magic" function, a custom print (just like BeforeSerialize & HasBeforeSerialize)
 * Custom print can be used for printing a custom reflected vector, for example.
 * Find the array size & correctly dump arrays.
 *
 * NAME OF TYPE!
 */

template<class T>
void
Dump(T const *object)
{
    using namespace metareflect;
    Class const *c = GetClass<T>();
    if (c == nullptr) {
        printf("Class not reflected.\n");
        return;
    }

    /* c->Print(object); */

    printf("%s {\n", c->Name());
    auto visitor = [](
            void const *instance,
            Field const *field,
            unsigned depth,
            Class::VisitType type) {
        if (type == Class::VisitType::ClassBegin) {
            Class const *visited = (Class const *)field->Type();
            printf("%.*s.%s = %s%s {\n",
                depth * 2, spaces,
                field->Name(),
                visited->Name(),
                field->Qualifier().isPointer ? " *" : "");
        } else if (type == Class::VisitType::ClassEnd) {
            printf("%.*s}\n", depth * 2, spaces);
        } else if (type == Class::VisitType::ClassMember) {
            printf("%.*s.%s = ", depth *2, spaces, field->Name());
            if (instance)
                field->Type()->Print(instance);
            else printf("nullptr");
            printf("\n");
        } else if (type == Class::VisitType::ArrayBegin) {
            printf("%.*s[\n", depth * 2, spaces);
        } else if (type == Class::VisitType::ArrayEnd) {
            printf("%.*s]\n", depth * 2, spaces);
        } else if (type == Class::VisitType::ArrayElement) {
            printf("%.*s", depth *2, spaces);
            if (instance)
                field->Type()->Print(instance);
            else printf("nullptr");
            printf("\n");
        }
    };
    c->Visit(object, visitor);
    printf("}\n");
}

int main()
{
    Point p;
    p.x = 10;
    p.y = 10;
    p.z = 0;

    ColoredPoint cp;
    cp.point = p;
    cp.color.r = 255;
    cp.color.g = 20;
    cp.color.b = 128;

    Object o;
    o.pPoint = &p;
    o.points[0] = p;
    o.points[1] = { 20, 20, 0 };
    o.points[2] = { 30, 30, 0 };
    o.children = nullptr;

    Dump(&p);
    printf("---\n");
    Dump(&cp);
    printf("---\n");
    Dump(&o);
    printf("---\n");

    auto c = metareflect::GetClass<Point>();
    auto x = c->FieldByName("x");
    printf("x = %d | %d\n", x->GetAs<int>(&p), p.x);
    printf("set x to 50\n");
    x->SetValue<int>(&p, 50);
    printf("x = %d | %d\n", x->GetAs<int>(&p), p.x);

    /* Simple compile-time reflection: */
    #if 0
    static_assert(metareflect::IsSerializable<Point>::value, "whoops");
    static_assert(!metareflect::HasAfterSerialize<Point>::value, "whoops");
    static_assert(!metareflect::HasBeforeSerialize<Point>::value, "whoops");
    static_assert(!metareflect::HasCustomSerialize<Point>::value, "whoops");
    #endif
    /* more to be added, as needed ... */

    /* Simple run-time reflection: */
    metareflect::Class const *point = metareflect::GetClass<Point>();
    assert(point->Fields().Length() == 3);
    assert(point->Functions().Length() == 1);

    for (auto &field : point->Fields()) {
        assert(*(field.Type()) == *(metareflect::GetType<int>()));
        assert(field.Flags() == metareflect::Field::kFlagsSerialized);
        assert(field.SerializedWidth() == 32);
        /* omitted qualifier assertions for brevity. */
    }

    auto const &func = point->Functions()[0];
    assert(*(func.ReturnType()->Type()) == *(metareflect::GetType<unsigned long>()));
    /* assert(func.Parameters().Length() == 1); */
    /* auto const &param0 = func.Parameters()[0]; */
    /* assert(*param0.Type() == *metareflect::GetType<Point>()); */
    /* assert(param0.Qualifier().isPointer); */
    /* 
     * Technically, all of the above is known at compile time, and can be folded
     * by the compiler into constant expressions.
     */
}

