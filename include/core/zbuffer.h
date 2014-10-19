#ifndef ZBUFFER_H
#define ZBUFFER_H

struct Triangle;
struct FrameBuffer;
class ZBuffer
{
public:
    ZBuffer();

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    void execute();

private:
    FrameBuffer *frameBuffer;
    void processBuffer(float x, float y, float zValue, Triangle &t);
};

#endif // ZBUFFER_H
