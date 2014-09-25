#ifndef PIPELINE_H
#define PIPELINE_H

#include "vertexshader.h"
#include "clipper.h"
#include "primitive.h"


enum ClipperType{
    SutherlandHodgman,
    WeilerAtherton
};

struct PipelineConfiguration{
    PrimitiveType primitive;
    ClipperType clipper;
};

class Pipeline
{
public:
    Pipeline();
    ~Pipeline();

    PipelineConfiguration getConfiguration() const;
    void setConfiguration(const PipelineConfiguration &value);

    void attachVertexShader(VertexShader *vertShader);

    void render();
    void clear();



private:

    void viewPortTransform();

    PipelineConfiguration configuration;
    VertexShader *vertShader;
    Clipper *clipper;
    Primitive primitive;
};


#endif // PIPELINE_H
