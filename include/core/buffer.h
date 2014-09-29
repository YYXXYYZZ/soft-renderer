#ifndef BUFFER_H
#define BUFFER_H
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

template <class T>
Buffer<T>::Buffer(int width, int height)
    :w(width),h(height)
{
    buffer = new T[width * height];
}

template <class T>
Buffer<T>::~Buffer()
{
    delete []buffer;
}

template <class T>
T &Buffer<T>::data(int x, int y)
{
    //WARNING: may improve?
    assert(x*w+y<w*h);
    return buffer[x*w+y];
}

struct FrameBuffer
{
    FrameBuffer(int width,int height);
    ~FrameBuffer();

    int w;
    int h;
    Buffer<float> *zBuffer;
    Buffer<vec3> *colorBuffer;
};

#endif // BUFFER_H
