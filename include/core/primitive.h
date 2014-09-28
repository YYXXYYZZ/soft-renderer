#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <glm/glm.hpp>

using glm::vec4;
using glm::vec3;

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
    vec4 p1;
    vec4 p2;
    vec4 p3;
    bool backFacing;

    /*
     *  algo: www.cnblogs.com/graphics/archive/2010/08/05/1793393.html
     */
    bool inside(const vec4&p) const{
        vec3 v0(p3 - p1);
        vec3 v1(p2 - p1);
        vec3 v2(p - p1);

        float dot00 = glm::dot(v0,v0);
        float dot01 = glm::dot(v0,v1);
        float dot02 = glm::dot(v0,v2);
        float dot11 = glm::dot(v1,v1);
        float dot12 = glm::dot(v1,v2);

        float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

        float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
        // if u out of range, return directly
        if (u < 0 || u > 1)
        {
            return false ;
        }

        float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
        // if v out of range, return directly
        if (v < 0 || v > 1)
        {
            return false ;
        }
        return u + v <= 1 ;
    }
};

class Primitive
{
public:
    Primitive();
    bool setup(PrimitiveType type,int count);
    bool setupByIndex(PrimitiveType type,int count);

private:
    vec4 *positionData;
    int   positionSize;
    int  *indexData;
    int   indexSize;
};

#endif // PRIMITIVE_H
