#ifndef PIPELINE_H
#define PIPELINE_H

#include "primitive.h"

enum ClipperType{
    SutherlandHodgman,
    WeilerAtherton
};

struct Config{
    PrimitiveType pri;
    int width;
    int height;
};

class Shader;
class ZBuffer;
class Culler;
class Clipper;
class FrameBuffer;

class Pipeline
{
public:
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

private:
    Config config;
    Clipper *clipper;
    Culler *culler;
    ZBuffer *zbuffer;
    Primitive *primitive;
    Shader *vertShader;
    Shader *fragShader;
    FrameBuffer *frameBuffer;
};


#endif // PIPELINE_H
