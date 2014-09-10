#ifndef CLIPPER_H
#define CLIPPER_H

#include <glm/glm.hpp>

class Clipper
{
public:
    Clipper();

    void initialize();
    virtual void execute();

    // for line
    // void Cohen_Sutherland();
    // void Liang_Barsky();

    // for polygon
    // void Sutherland_Hodgman();
    // void Weiler_Atherton();

protected:
    glm::vec4 *position;
    bool canClip;
    int size;
};

#endif // CLIPPER_H
