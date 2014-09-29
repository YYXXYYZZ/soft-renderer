#include <iostream>
#include <core/primitive.h>

using namespace std;
ostream & operator <<(ostream &os,const Triangle &t){

    os << "========================\n";
    os << t.p1[0] <<" " << t.p1[1] << " " << t.p1[2] << endl;
    os << t.p2[0] <<" " << t.p2[1] << " " << t.p2[2] << endl;
    os << t.p3[0] <<" " << t.p3[1] << " " << t.p3[2] << endl;
    os << "========================\n";
    return os;
}

int main()
{
    Triangle t;
    t.p1 = glm::vec4(-0.5f,0.0f,0.0f,1.0f);
    t.p2 = glm::vec4(1.0f,0.5f,0.0f,1.0f);
    t.p3 = glm::vec4(0.0f,-0.5f,0.0f,1.0f);

    vec2 min;
    vec2 max;
    std::set<float> result;
    t.extremeValue(min,max);
    t.intersect(0.5f,min.x,max.x,result);

    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        cout << *iter << endl;
    }
}
