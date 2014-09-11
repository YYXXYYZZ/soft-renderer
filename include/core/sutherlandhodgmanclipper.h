#ifndef SUTHERLANDHODGMANCLIPPER_H
#define SUTHERLANDHODGMANCLIPPER_H

#include "clipper.h"
#include <vector>
using std::vector;

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
    void fillData(vector<glm::vec4> &input);
    void clip(vector<glm::vec4>&input, vector<glm::vec4>&output, Boundary b);
    bool inside(glm::vec4 p1,Boundary b);
    glm::vec4 intersect(glm::vec4 p1, glm::vec4 p2, Boundary b);

};

#endif // SUTHERLANDHODGMANCLIPPER_H
