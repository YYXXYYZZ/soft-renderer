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
    inline T& dataAt(int x,int y);
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
    data = new T[w * h];
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

class FrameBuffer
{
public:
    FrameBuffer(int width,int height,vec3 clearColor);
    ~FrameBuffer();

    vec3 *colorBuffer() const;
    void clearBuffer() const;
private:
    int _width;
    int _height;
    vec3 _clearColor;
    Buffer<float> *_zBuffer;
    Buffer<vec3> *_colorBuffer;

    friend class ZBuffer;
};

#endif // BUFFER_H
