#ifndef PIPELINE_H
#define PIPELINE_H

#include "primitive.h"

class VertexShader;
class FragShader;
class ZBuffer;
class Culler;
class Clipper;
class FrameBuffer;

class Pipeline
{
public:
    struct Config{
        int width;
        int height;
        glm::vec3 clearColor;
        PrimitiveType primitiveType;
        bool renderByIndex;
    };

    Pipeline();
    ~Pipeline();

    void render();
    void clear();
    void update();
    void attachVertShader(VertexShader *vShader);
    void attachFragShader(FragShader *fShader);
    vec3 *getColorBuffer() const;

    Config getConfig() const;
    void setConfig(const Config &value);

private:
    Config config;
    Clipper *clipper;
    Culler *culler;
    ZBuffer *zbuffer;
    Primitive *primitive;
    VertexShader *vertShader;
    FragShader *fragShader;
    FrameBuffer *frameBuffer;
};


#endif // PIPELINE_H
