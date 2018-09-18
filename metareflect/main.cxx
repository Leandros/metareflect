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


struct DumpVisitor : public metareflect::ClassVisitor {
    virtual void
    ClassBegin(metareflect::Class const *clazz, int) override
    {
        printf("%s {\n", clazz->Name());
    }

    virtual void
    ClassEnd(metareflect::Class const *, int depth) override
    {
        printf("%.*s}\n", depth * 2, spaces);
    }

    virtual void
    ClassMember(metareflect::Field const *field, int depth) override
    {
        bool isPointer = field->Qualifier().isPointer;
        printf("%.*s.%s = ", depth * 2, spaces, field->Name());
        if (isPointer)
            printf("&");
    }

    virtual void
    ArrayBegin(metareflect::Type const *, int, int) override
    {
        printf("[\n");
    }

    virtual void
    ArrayEnd(metareflect::Type const *, int depth) override
    {
        printf("%.*s]\n", depth * 2, spaces);
    }

    virtual void
    ArrayElement(metareflect::Type const *, int depth, int arrayElem) override
    {
        printf("%.*s[%d] = ", depth * 2, spaces, arrayElem);
    }


    virtual void
    Primitive(metareflect::Type const *type, void const *instance) override
    {
        if (instance == nullptr) {
            printf("nullptr\n");
            return;
        }

        printf("%s{", type->Name());
        type->Dump(instance);
        printf("}\n");
    }

    virtual void
    String(metareflect::Type const *, void const *instance) override
    {
        if (instance)
            printf("string{%s}\n", *(char const **)instance);
        else
            printf("string{}\n");
    }
};

struct JsonVisitor : public metareflect::ClassVisitor {
    int nValues = 0;
    int nArray = 0;

    virtual void
    ClassBegin(metareflect::Class const *clazz, int) override
    {
        nValues = 1;
        printf("{\"__type\":\"%llu\"", clazz->Hash());
    }

    virtual void
    ClassEnd(metareflect::Class const *, int) override
    {
        printf("}");
    }

    virtual void
    ClassMember(metareflect::Field const *field, int) override
    {
        if (nValues++ != 0)
            printf(",");
        printf("\"%s\":", field->Name());
    }

    virtual void
    ArrayBegin(metareflect::Type const *, int, int) override
    {
        nArray = 0;
        printf("[");
    }

    virtual void
    ArrayEnd(metareflect::Type const *, int) override
    {
        printf("]");
    }

    virtual void
    ArrayElement(metareflect::Type const *, int, int) override
    {
        if (nArray++ > 0)
            printf(",");
    }

    virtual void
    Primitive(metareflect::Type const *type, void const *instance) override
    {
        if (instance) {
            double val = ToDouble(type, instance);
            printf("%.17g", val);
        } else {
            printf("{}");
        }
    }

    virtual void
    String(metareflect::Type const *, void const *instance) override
    {
        if (instance)
            printf("\"%s\"", *(char const **)instance);
        else
            printf("\"\"");
    }

    double
    ToDouble(metareflect::Type const *type, void const *instance)
    {
        assert(!type->IsClass() && "type must be primitive");
        static uint64_t const typeHashes[] = {
            metareflect::GetType<bool>()->Hash(),
            metareflect::GetType<char>()->Hash(),
            metareflect::GetType<short>()->Hash(),
            metareflect::GetType<int>()->Hash(),
            metareflect::GetType<long>()->Hash(),
            metareflect::GetType<long long>()->Hash(),
            metareflect::GetType<float>()->Hash(),
            metareflect::GetType<double>()->Hash(),
            metareflect::GetType<long double>()->Hash(),
            metareflect::GetType<unsigned char>()->Hash(),
            metareflect::GetType<unsigned short>()->Hash(),
            metareflect::GetType<unsigned int>()->Hash(),
            metareflect::GetType<unsigned long>()->Hash(),
            metareflect::GetType<unsigned long long>()->Hash(),
        };

        double ret = 0.0;
        uint64_t hash = type->Hash();
        if (hash == typeHashes[0])
            ret = *(bool *)instance;
        else if (hash == typeHashes[1])
            ret = *(char *)instance;
        else if (hash == typeHashes[2])
            ret = *(short *)instance;
        else if (hash == typeHashes[3])
            ret = *(int *)instance;
        else if (hash == typeHashes[4])
            ret = *(long *)instance;
        else if (hash == typeHashes[5])
            ret = *(long long *)instance;
        else if (hash == typeHashes[6])
            ret = *(float *)instance;
        else if (hash == typeHashes[7])
            ret = *(double *)instance;
        else if (hash == typeHashes[8])
            ret = *(long double *)instance;
        else if (hash == typeHashes[9])
            ret = *(unsigned char *)instance;
        else if (hash == typeHashes[10])
            ret = *(unsigned short *)instance;
        else if (hash == typeHashes[11])
            ret = *(unsigned int *)instance;
        else if (hash == typeHashes[12])
            ret = *(unsigned long *)instance;
        else if (hash == typeHashes[13])
            ret = *(unsigned long long *)instance;
        return ret;
    }
};


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

    DumpVisitor visitor0;
    c->Visit(object, &visitor0);
    printf("\n");
    JsonVisitor visitor1;
    c->Visit(object, &visitor1);
    printf("\n");
}

int main()
{
    Point p;
    p.x = 10;
    p.y = 10;
    p.z = 0;

    Dump(&p);
    printf("---\n");

    ColoredPoint cp;
    cp.point = p;
    cp.color.r = 255;
    cp.color.g = 20;
    cp.color.b = 128;
    cp.name = "My Point";

    Dump(&cp);
    printf("---\n");

    Object parent{};

    Object o{};
    o.pPoint = &p;
    o.points[0] = p;
    o.points[1] = { 20, 20, 0 };
    o.points[2] = { 30, 30, 0 };
    o.children = nullptr;
    o.parent = &parent;

    Dump(&o);
    printf("---\n");

    auto c = metareflect::GetClass<Point>();
    auto x = c->FieldByName("x");
    printf("x = %d | %d\n", x->GetAs<int>(&p), p.x);
    printf("set x to 50\n");
    x->SetValue<int>(&p, 50);
    printf("x = %d | %d\n", x->GetAs<int>(&p), p.x);

    std::vector<Point> vec;
    vec.push_back({ 1, 1, 1 });
    vec.push_back({ 2, 2, 2 });
    vec.push_back({ 3, 3, 3 });
    vec.push_back({ 4, 4, 4 });
    Dump(&vec);


    User user;
    user.id = 42;
    user.name = "John";
    user.pets.push_back("Buddy");
    user.pets.push_back("Cooper");

    Dump(&user);

    /* Simple compile-time reflection: */
    #if 0
    static_assert(metareflect::IsSerializable<Point>::value, "whoops");
    static_assert(!metareflect::HasAfterSerialize<Point>::value, "whoops");
    static_assert(!metareflect::HasBeforeSerialize<Point>::value, "whoops");
    static_assert(!metareflect::HasCustomSerialize<Point>::value, "whoops");
    #endif
    /* more to be added, as needed ... */

    /* Simple run-time reflection: */
    /* metareflect::Class const *point = metareflect::ClassResolver<Point>::Get(); */
    /* assert(point->Fields().Length() == 3); */
    /* assert(point->Functions().Length() == 1); */

    /* for (auto &field : point->Fields()) { */
        /* assert(*(field.Type()) == *(metareflect::GetType<int>())); */
        /* assert(field.Flags() == metareflect::Field::kFlagsSerialized); */
        /* assert(field.SerializedWidth() == 32); */
        /* omitted qualifier assertions for brevity. */
    /* } */

    /* auto const &func = point->Functions()[0]; */
    /* assert(*(func.ReturnType()->Type()) == *(metareflect::GetType<unsigned long>())); */
    /* assert(func.Parameters().Length() == 1); */
    /* auto const &param0 = func.Parameters()[0]; */
    /* assert(*param0.Type() == *metareflect::GetType<Point>()); */
    /* assert(param0.Qualifier().isPointer); */
    /*
     * Technically, all of the above is known at compile time, and can be folded
     * by the compiler into constant expressions.
     */
}

