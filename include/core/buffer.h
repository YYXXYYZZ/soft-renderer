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
    T& dataAt(int x,int y);
    T * buffer();
private:
    int w;
    int h;
    T *data;
};

template <class T>
Buffer<T>::Buffer(int width, int height)
    :w(width),h(height)
{
    data = new T[width * height];
}

template <class T>
Buffer<T>::~Buffer()
{
    delete []data;
}

template <class T>
T &Buffer<T>::dataAt(int x, int y)
{
    //WARNING: may improve?
    assert(y*w+x<w*h);
    return data[y*w+x];
}

template <class T>
T *Buffer<T>::buffer()
{
    return data;
}

struct FrameBuffer
{
    int w;
    int h;
    Buffer<float> *zBuffer;
    Buffer<vec3> *colorBuffer;
};

#endif // BUFFER_H
