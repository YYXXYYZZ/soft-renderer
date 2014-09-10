#ifndef SUTHERLANDHODGMANCLIPPER_H
#define SUTHERLANDHODGMANCLIPPER_H

#include "clipper.h"

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
    void clipPoint(glm::vec4 p, Boundary winEdge,
                   glm::vec4 *pOut, int *cnt,
                   glm::vec4 *first[],
                   glm::vec4 *s);
    bool cross(glm::vec4 p1,glm::vec4 p2,Boundary winEdge);
    bool inside(glm::vec4 p1,Boundary b);

};

#endif // SUTHERLANDHODGMANCLIPPER_H
