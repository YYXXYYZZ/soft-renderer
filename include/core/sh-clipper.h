#ifndef SHClipper_H
#define SHClipper_H

#include "clipper.h"
#include <vector>
#include <list>
using std::vector;
using glm::vec4;

/**
 *  Sutherland-Hodgman clip algorithm
 *
 **/

class SHClipper : public Clipper
{
public:
    enum Boundary{
        Left,Right,
        Bottom,Top,
        Near,Far
    };

    SHClipper();
    void execute();

    static void polygonToTriangle(vector<PointObject> &inPolygon,
                                  vector<Triangle> &out);
private:
    void clip(vector<PointObject> &input, vector<PointObject> &output, Boundary b);
    bool inside(PointObject p, Boundary b);
    PointObject intersect(PointObject v1, PointObject p2, Boundary b);
    void Sutherland_Hodgman();

};

#endif // SHClipper_H
