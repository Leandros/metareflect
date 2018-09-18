#include <string.h>
#include <stdlib.h>
#include "metareflect.hxx"
#include <string>
#include <vector>

CLASS() Point
{
    META_OBJECT

public:
    PROPERTY(Serialized, Width=32)
    signed x;

    PROPERTY(Serialized)
    int32_t y;

    PROPERTY(Serialized)
    size_t z;

    FUNCTION()
    size_t Hash() const
    {
        return x ^ y ^ z;
    }
};

UNION() RGBColor
{
    META_OBJECT

public:
    PROPERTY(Serialized)
    uint32_t rgb;
    PROPERTY()
    struct {
        unsigned char _;
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
};

CLASS() ColoredPoint
{
    META_OBJECT

public:
    PROPERTY(Serialized)
    Point point;

    PROPERTY(Serialized, Width=24)
    RGBColor color;

    PROPERTY(Serialized, CString)
    char const *name;
};

CLASS() Object
{
    META_OBJECT
public:

    PROPERTY(Serialized)
    Point *pPoint;

    PROPERTY(Serialized)
    Point points[3];

    PROPERTY()
    Object *children;

    PROPERTY()
    Object *parent;
};


CLASS() NPCObject
{
    META_OBJECT

public:
    PROPERTY(Serialized)
    Point position;

    FUNCTION()
    char const *GetName() const noexcept
    {
        return m_name;
    }

    FUNCTION()
    void SetName(char const *name) noexcept
    {
        free(m_name);
        m_name = strdup(name);
    }

    template<class Serializer>
    bool Serialize(Serializer &serializer) noexcept
    {
        serializer.SerializeString(m_name, strlen(m_name));
        return true;
    }

private:
    char *m_name = nullptr;
};

template<class T>
using vector = std::vector<T>;
using string = std::string;


CLASS() User
{
public:
    PROPERTY(Serialized)
    uint64_t id;

    PROPERTY(Serialized)
    string name;

    PROPERTY(Serialized)
    vector<string> pets;
};

