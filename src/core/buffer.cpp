#include "core/buffer.h"



FrameBuffer::FrameBuffer(int width, int height, glm::vec3 clearColor)
    :_width(width),_height(height),_clearColor(clearColor)
{
    _zBuffer = new Buffer<float>(width,height);
    _colorBuffer = new Buffer<vec3>(width,height);
    clearBuffer();
}

FrameBuffer::~FrameBuffer()
{
    delete _zBuffer;
    delete _colorBuffer;
}

glm::vec3 *FrameBuffer::colorBuffer() const
{
    _colorBuffer->buffer();
}


void FrameBuffer::clearBuffer() const
{
#pragma omp parallel for
    for (auto i = 0; i < _width*_height; ++i) {
        _zBuffer->buffer()[i] = FLT_MAX;
        _colorBuffer->buffer()[i] = _clearColor;
    }
}
