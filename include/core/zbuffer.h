#ifndef ZBUFFER_H
#define ZBUFFER_H

struct Triangle;
struct FrameBuffer;
class FragShader;
class ZBuffer
{
public:
    ZBuffer();

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    FragShader *getFragShader() const;
    void setFragShader(FragShader *value);

    void execute();


private:
    FragShader *fragShader;
    FrameBuffer *frameBuffer;
    void processBuffer(float x, float y, float zValue, Triangle &t);
};

#endif // ZBUFFER_H
