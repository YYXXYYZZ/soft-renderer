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
    frameBuffer = nullptr;
}

Pipeline::~Pipeline()
{
    delete clipper;
    delete culler;
    delete zbuffer;
    delete primitive;
    if (frameBuffer)
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

vec3 *Pipeline::getColorBuffer() const
{
    return frameBuffer->colorBuffer->buffer();
}

void Pipeline::initFrameBuffer()
{
    frameBuffer = new FrameBuffer;
    frameBuffer->w = config.width;
    frameBuffer->h = config.height;
    frameBuffer->zBuffer = new Buffer<float>(frameBuffer->w,frameBuffer->h);
    frameBuffer->colorBuffer = new Buffer<vec3>(frameBuffer->w,frameBuffer->h);

    for (int i = 0; i < config.width*config.height; ++i) {
        frameBuffer->zBuffer->buffer()[i] = FLT_MAX;
        frameBuffer->colorBuffer->buffer()[i] = config.clearColor;
    }
    zbuffer->setFrameBuffer(frameBuffer);
}

Pipeline::Config Pipeline::getConfig() const
{
    return config;
}

void Pipeline::setConfig(const Config &value)
{
    config = value;
    initFrameBuffer();
}

void Pipeline::render()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
        return;
    }
    vertShader->execute();
    //TODO fix me :6
    primitive->setup(config.primitiveType,36);
    clipper->execute();
    culler->execute();
    zbuffer->execute();
}

//TODO clear
void Pipeline::clear()
{
    GPUMemory::dealloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT);
}


