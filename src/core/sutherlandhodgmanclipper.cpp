#include "core/sutherlandhodgmanclipper.h"

SutherlandHodgmanClipper::SutherlandHodgmanClipper()
{
}

void SutherlandHodgmanClipper::execute()
{
    Sutherland_Hodgman();
}

void SutherlandHodgmanClipper::Sutherland_Hodgman()
{
    if(!canClip)
        return;

    // "first " holds pointer to first point processed for a
    // bounary;
    // "s" holds most recent point processed for boundary.

    const int nClip = 6;
    glm::vec4 * first[nClip] = {
        0,0,0,
        0,0,0
    };
    glm::vec4 s[nClip];
    int cnk = 0;

    for (int k = 0; k < size; ++k) {
        clipPoint();
    }
}

void SutherlandHodgmanClipper::clipPoint(glm::vec4 p, Boundary winEdge,
                                         glm::vec4 *pOut, int *cnt,
                                         glm::vec4 *first[],glm::vec4 *s)
{
    // no need to specify winMax and winMin because this is a
    // normal projection vloume
    glm::vec4 iPt;

    // if no previous point exists for this clipping boundary,
    // save this point.
    if(!first[winEdge])
        first[winEdge] = &p;
    else{
        if(cross(p,s[winEdge])){
            iPt = intersect(p,winEdge);
            if(winEdge < Far)
                clipPoint(iPt,winEdge+1,pOut,cnt,first,s);
        }
    }

    s[winEdge] = p;

}

// p1 and p2 whether cross to edge or not,
// if they don't have same inside value, then it is!
bool SutherlandHodgmanClipper::cross(glm::vec4 p1, glm::vec4 p2, Boundary winEdge)
{
    if (inside(p1,winEdge) == inside(p2,winEdge))
        return false;
    return true;
}

bool SutherlandHodgmanClipper::inside(glm::vec4 p1, Boundary b)
{
    switch (b) {
    case Left:
        if(p1[0] < -1)
            return false;
        break;
    case Right:
        if(p1[0] > 1)
            return false;
        break;
    case Bottom:
        if(p1[1] < -1)
            return false;
        break;
    case Top:
        if(p1[1] > 1)
            return false;
        break;
    case Near:
        if(p1[2] > 1)
            return false;
        break;
    case Far:
        if(p1[2] < -1)
            return false;
        break;

    default:
        break;
    }
    return true;
}
