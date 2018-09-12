#include <string.h>
#include <stdlib.h>
#include "metareflect.hxx"

CLASS() Point
{
    META_OBJECT

public:
    PROPERTY(Serialized, Width=32)
    signed int x;

    PROPERTY(Serialized)
    int y;

    PROPERTY(Serialized)
    int z;

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
    PROPERTY()
    int rgb;
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
};

CLASS() Object
{
    META_OBJECT
public:

    PROPERTY()
    Point *pPoint;

    PROPERTY()
    Point points[8];

    PROPERTY()
    Object *children;
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

