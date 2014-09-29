#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <glm/glm.hpp>
using glm::vec3;

template<typename T>
class Buffer
{
public:
    Buffer(int width,int height);
    ~Buffer();
    T& data(int x,int y);
private:
    int w;
    int h;
    T *buffer;
};

struct FrameBuffer
{
    int w;
    int h;
    Buffer<float> *zBuffer;
    Buffer<vec3> *colorBuffer;
};

class ZBuffer
{
public:
    ZBuffer();

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    void execute();

private:
    FrameBuffer *frameBuffer;
    void processBuffer(float x, float y, float zValue);
};

#endif // ZBUFFER_H
