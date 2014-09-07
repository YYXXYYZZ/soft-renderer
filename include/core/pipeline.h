#ifndef PIPELINE_H
#define PIPELINE_H

#include "vertexshader.h"

class PipeLine
{
public:
    PipeLine();

    void attachVertexShader(VertexShader *vertShader);

    void execute();

private:
    VertexShader *vertShader;
};

#endif // PIPELINE_H
