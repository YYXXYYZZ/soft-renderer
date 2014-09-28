#ifndef SUTHERLANDHODGMANCLIPPER_H
#define SUTHERLANDHODGMANCLIPPER_H

#include "clipper.h"
#include <vector>
#include <list>
using std::vector;
using glm::vec4;

class SutherlandHodgmanClipper : public Clipper
{
public:
    enum Boundary{
        Left,Right,
        Bottom,Top,
        Near,Far
    };

    SutherlandHodgmanClipper();
    void execute();

    void polygonToTriangle(vector<vec4> inPolygon, vector<Triangle> &out);
private:
    void clip(vector<vec4> &input, vector<vec4> &output, Boundary b);
    bool inside(vec4 p1,Boundary b);
    vec4 intersect(vec4 p1, vec4 p2, Boundary b);
    // subdivision polygon to triangle
    void Sutherland_Hodgman();

};

#endif // SUTHERLANDHODGMANCLIPPER_H
