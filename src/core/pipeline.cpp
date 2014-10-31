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

vec3 *Pipeline::getColorBuffer() const
{
    return frameBuffer->colorBuffer();
}

Pipeline::Config Pipeline::getConfig() const
{
    return config;
}

void Pipeline::setConfig(const Config &value)
{
    config = value;
    if(frameBuffer)
        delete frameBuffer;
    frameBuffer = new FrameBuffer(config.width,config.height,config.clearColor);
    zbuffer->setFrameBuffer(frameBuffer);
}


#include <ctime>
#include <cstdio>

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

    clock_t start,end;
    start = clock();
    vertShader->execute();
    end = clock();
    double dur = (double)(end - start);
    printf("vertShader Use Time:%f\n",(dur/CLOCKS_PER_SEC));
    //TODO fix me :6
    start = clock();
    primitive->setup(config.primitiveType,36);
    end = clock();
    dur = (double)(end - start);
    printf("primitive Use Time:%f\n",(dur/CLOCKS_PER_SEC));

    start = clock();
    clipper->execute();
    end = clock();
    dur = (double)(end - start);
    printf("clipper Use Time:%f\n",(dur/CLOCKS_PER_SEC));

    start = clock();
    culler->execute();
    end = clock();
    dur = (double)(end - start);
    printf("culler Use Time:%f\n",(dur/CLOCKS_PER_SEC));

    start = clock();
    zbuffer->execute();
    end = clock();
    dur = (double)(end - start);
    printf("zbuffer Use Time:%f\n",(dur/CLOCKS_PER_SEC));
}

/**
 * @brief Pipeline::clear remove unused memory
 *  this two global variable should invisible to client
 */
void Pipeline::clear()
{
    GPUMemory::dealloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT);
    GPUMemory::dealloc<Triangle>(Constant::SF_CLIPOUT);
}

void Pipeline::update()
{
    clear();
    frameBuffer->clearBuffer();
    render();
}


