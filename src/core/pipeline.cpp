#include "core/pipeline.h"
#include "core/gpumemory.h"
#include "core/constant.h"
#include "core/sh-clipper.h"
#include "core/culler.h"
#include "core/clipper.h"
#include "core/zbuffer.h"
#include "core/vertexshader.h"
#include "core/buffer.h"
#include <iostream>

Pipeline::Pipeline()
{
    clipper = new SHClipper;
    culler = new Culler;
    zbuffer = new ZBuffer;
    primitive = new Primitive;
}

Pipeline::~Pipeline()
{
    delete clipper;
    delete culler;
    delete zbuffer;
    delete primitive;
    if(frameBuffer)
        delete frameBuffer;

}

void Pipeline::attachVertShader(Shader *vShader)
{
    vertShader = vShader;
}

void Pipeline::attachFragShader(Shader *fShader)
{
    fragShader = fShader;
}
FrameBuffer *Pipeline::getFrameBuffer() const
{
    return frameBuffer;
}

void Pipeline::setFrameBuffer(FrameBuffer *value)
{
    frameBuffer = value;
}

Config Pipeline::getConfig() const
{
    return config;
}

void Pipeline::setConfig(const Config &value)
{
    config = value;
    frameBuffer = new FrameBuffer(value.width,value.height);
    zbuffer->setFrameBuffer(frameBuffer);
}

void Pipeline::render()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
        return;
    }
    vertShader->execute();
    //TODO fix me :6
    primitive->setup(TRIANGLES,36);

    clipper->execute();
    culler->execute();
    zbuffer->execute();
}

//TODO clear
void Pipeline::clear()
{
    GPUMemory::dealloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT);
}


