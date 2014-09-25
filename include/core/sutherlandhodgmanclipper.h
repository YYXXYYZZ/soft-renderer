#ifndef SUTHERLANDHODGMANCLIPPER_H
#define SUTHERLANDHODGMANCLIPPER_H

#include "clipper.h"
#include <vector>
#include <list>
using std::vector;
using std::list;
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
    void Sutherland_Hodgman();

private:
    void clip(list<vec4> &input, list<vec4> &output, Boundary b);
    bool inside(vec4 p1,Boundary b);
    vec4 intersect(vec4 p1, vec4 p2, Boundary b);
    // subdivision polygon to triangle
    void polygonToTriangle(list<vec4> polygon, vector<Triangle> &out);

};

#endif // SUTHERLANDHODGMANCLIPPER_H
