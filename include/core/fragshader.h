#ifndef FRAGSHADER_H
#define FRAGSHADER_H

#include "core/shader.h"

class FragShader : public Shader
{
public:
    FragShader();

    virtual void execute() override;
    void setArgument();

protected:
    void initialize();
    void iterationCompute(int step);
    int  iterationTimes();

private:

};

#endif // FRAGSHADER_H
