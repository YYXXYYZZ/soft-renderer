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

    virtual void execute() override;
    void setIterationCompute(vec3 (*iterationCompute)(PointObject &,Triangle &));


    vec3 fragColor() const;

private:
    vec3 (*iterationCompute)(PointObject &point,Triangle &t);
    void setArgument(PointObject *point, Triangle *t);

    PointObject *point;
    Triangle *primitive;
    vec3 frag_color;

    friend class ZBuffer;

};

#endif // FRAGSHADER_H
