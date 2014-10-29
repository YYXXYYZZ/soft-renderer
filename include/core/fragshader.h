#ifndef FRAGSHADER_H
#define FRAGSHADER_H

#include <glm/vec3.hpp>
#include "core/shader.h"

using glm::vec3;

struct Triangle;
class PointObject;
class FragShader : public Shader
{
public:
    FragShader();
    void setHandle(vec3 (*handle)(PointObject &,Triangle &));
    vec3 fragColor() const;

private:
    void execute(PointObject *point, Triangle *t);
    vec3 (*handle)(PointObject &point,Triangle &t);
    void setArgument(PointObject *point, Triangle *t);
    vec3 frag_color;

    friend class ZBuffer;
};

#endif // FRAGSHADER_H
