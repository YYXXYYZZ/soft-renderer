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

    if (frameBuffer){
        delete frameBuffer->zBuffer;
        delete frameBuffer->colorBuffer;
        delete frameBuffer;
    }

    clear();
    GPUMemory::dealloc<PointObject>(Constant::SF_POSITION);

}

void Pipeline::attachVertShader(VertexShader *vShader)
{
    vertShader = vShader;
}

void Pipeline::attachFragShader(FragShader *fShader)
{
    fragShader = fShader;
    zbuffer->setFragShader(fShader);
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

void Pipeline::makeFrameBuffer()
{
    frameBuffer = new FrameBuffer;
    frameBuffer->w = config.width;
    frameBuffer->h = config.height;
    frameBuffer->zBuffer = new Buffer<float>(frameBuffer->w,frameBuffer->h);
    frameBuffer->colorBuffer = new Buffer<vec3>(frameBuffer->w,frameBuffer->h);
    fillFrameBuffer();
    zbuffer->setFrameBuffer(frameBuffer);
}

void Pipeline::fillFrameBuffer()
{
#pragma omp parallel for
    for (int i = 0; i < config.width*config.height; ++i) {
        frameBuffer->zBuffer->buffer()[i] = FLT_MAX;
        frameBuffer->colorBuffer->buffer()[i] = config.clearColor;
    }
}

Pipeline::Config Pipeline::getConfig() const
{
    return config;
}

void Pipeline::setConfig(const Config &value)
{
    config = value;
    makeFrameBuffer();
}

void Pipeline::render()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
        return;
    }

    if (!fragShader) {
        std::cerr << "Warning: null fragment shader! "<<std::endl;
        return;
    }

    vertShader->execute();
    //TODO fix me :6
    primitive->setup(config.primitiveType,36);
    clipper->execute();
    culler->execute();
    zbuffer->execute();
}

/**
 * @brief Pipeline::clear remove unused memory
 *  this two invisible to client
 */
void Pipeline::clear()
{
    GPUMemory::dealloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT);
    GPUMemory::dealloc<Triangle>(Constant::SF_CLIPOUT);
}

void Pipeline::update()
{
    clear();
    fillFrameBuffer();
    render();
}


