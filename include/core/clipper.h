#ifndef CLIPPER_H
#define CLIPPER_H

#include <core/primitive.h>
class Clipper
{
public:
    Clipper();
    virtual ~Clipper();
    void initialize();
    virtual void execute() = 0;

    // for line
    // void Cohen_Sutherland();
    // void Liang_Barsky();

    // for polygon
    // void Sutherland_Hodgman();
    // void Weiler_Atherton();

protected:
    Triangle *triangle;
    size_t primitiveCount;
    bool canClip;
};

#endif // CLIPPER_H
