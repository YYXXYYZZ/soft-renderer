#ifndef ZBUFFER_H
#define ZBUFFER_H

struct Triangle;
struct FrameBuffer;
class FragShader;
class ZBuffer
{
public:
    ZBuffer();
    void execute();

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    FragShader *getFragShader() const;
    void setFragShader(FragShader *value);

private:
    FragShader *fragShader;
    FrameBuffer *frameBuffer;
    void processBuffer(int _x, int _y, float zValue, Triangle &t);
};

#endif // ZBUFFER_H
