#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <glm/glm.hpp>

enum PrimitiveType{
    POINTS,
    LINES,LINESTRIP,LINElOOP,
    TRIANGLES,TRIANGLEFAN
};

struct Point{
    glm::vec4 p1;
};

struct Line{
    glm::vec4 p1;
    glm::vec4 p2;
};

struct Triangle{
    glm::vec4 p1;
    glm::vec4 p2;
    glm::vec4 p3;
};

class Primitive
{
public:
    Primitive();
    bool setup(PrimitiveType type,int count);
    bool setupByIndex(PrimitiveType type,int count);

private:
    int positionSize;
    glm::vec4 *positionData;
    int indexSize;
    int *indexData;
};

#endif // PRIMITIVE_H
