#ifndef PIPELINE_H
#define PIPELINE_H

#include "primitive.h"

enum ClipperType{
    SutherlandHodgman,
    WeilerAtherton
};


class Shader;
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
    };

    Pipeline();
    ~Pipeline();

    void render();
    void clear();
    void attachVertShader(Shader *vShader);
    void attachFragShader(Shader *fShader);

    Config getConfig() const;
    void setConfig(const Config &value);

    FrameBuffer *getFrameBuffer() const;
    void setFrameBuffer(FrameBuffer *value);

    vec3* getColorBuffer() const;

private:
    Config config;
    Clipper *clipper;
    Culler *culler;
    ZBuffer *zbuffer;
    Primitive *primitive;
    Shader *vertShader;
    Shader *fragShader;
    FrameBuffer *frameBuffer;

    void initFrameBuffer();
};


#endif // PIPELINE_H
