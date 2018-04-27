#include <string.h>
#include <stdlib.h>
#include "metareflect.hxx"

CLASS() Point
{
    META_OBJECT

public:
    PROPERTY(Serialized, Width=)
    int x;

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


CLASS() ColoredPoint
{
    META_OBJECT

public:
    PROPERTY(Serialized)
    Point point;

    PROPERTY(Serialized, Width=24)
    union {
        int rgb;
        struct {
            char _;
            char b;
            char g;
            char r;
        };
    };
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
        m_name = _strdup(name);
    }

    template<class Serializer>
    FUNCTION()
    bool Serialize(Serializer &serializer) noexcept
    {
        serializer.SerializeString(m_name, strlen(m_name));
        return true;
    }

private:
    char *m_name = nullptr;
};

