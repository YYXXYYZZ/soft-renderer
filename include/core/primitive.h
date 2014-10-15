#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <glm/glm.hpp>
#include <set>
#include "core/vertex.h"

using glm::vec4;
using glm::vec3;
using glm::vec2;

enum PrimitiveType{
    POINTS,
    LINES,LINESTRIP,LINElOOP,
    TRIANGLES,TRIANGLEFAN
};

struct Point{
    vec4 p1;
};

struct Line{
    vec4 p1;
    vec4 p2;
};

struct Triangle{

    vec3 normal() const;
    vec4 downPoint() const;
    bool inside(const PointObject &p) const;
    void extremeValue(vec2 &_min, vec2 &_max) const;
    void intersect(float y,float min_x,float max_x, std::set<float> &result);

    PointObject p1;
    PointObject p2;
    PointObject p3;
    bool backFacing;

};

class Primitive
{
public:
    Primitive();
    bool setup(PrimitiveType type,int count);
    bool setupByIndex(PrimitiveType type,int count);

private:
    PointObject *verteices;
    int   vertexCount;
    int  *indexData;
    int   indexSize;
};

#endif // PRIMITIVE_H
