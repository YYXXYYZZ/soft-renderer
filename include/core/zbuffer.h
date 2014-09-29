#ifndef ZBUFFER_H
#define ZBUFFER_H

class FrameBuffer;
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
