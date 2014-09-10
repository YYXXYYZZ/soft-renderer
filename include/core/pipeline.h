#ifndef PIPELINE_H
#define PIPELINE_H

#include "vertexshader.h"
#include "clipper.h"

class PipeLine
{
public:
    PipeLine();

    void attachVertexShader(VertexShader *vertShader);
    void attachClipper(Clipper *clipper);

    void execute();

private:
    VertexShader *vertShader;
    Clipper *clipper;
};

#endif // PIPELINE_H
