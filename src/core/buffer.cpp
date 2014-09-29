#include "core/buffer.h"

FrameBuffer::FrameBuffer(int width, int height)
    :w(width),h(height)
{
    zBuffer = new Buffer<float>(w,h);
    colorBuffer = new Buffer<vec3>(w,h);
}

FrameBuffer::~FrameBuffer()
{
    delete zBuffer;
    delete colorBuffer;
}
