#ifndef ZBUFFER_H
#define ZBUFFER_H

struct Triangle;
struct FrameBuffer;
class Shader;
class ZBuffer
{
public:
    ZBuffer();

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    Shader *getFragShader() const;
    void setFragShader(Shader *value);

    void execute();

private:
    Shader *fragShader;
    FrameBuffer *frameBuffer;
    void processBuffer(float x, float y, float zValue, Triangle &t);
};

#endif // ZBUFFER_H
