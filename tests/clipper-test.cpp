#include <iostream>
#include <core/sh-clipper.h>
#include <core/gpumemory.h>
#include <core/constant.h>

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

ostream & operator <<(ostream &os,const Triangle &t){

    os << "========================\n";
    os << t.p1.pos()[0] <<" " << t.p1.pos()[1] << " " << t.p1.pos()[2] << endl;
    os << t.p2.pos()[0] <<" " << t.p2.pos()[1] << " " << t.p2.pos()[2] << endl;
    os << t.p3.pos()[0] <<" " << t.p3.pos()[1] << " " << t.p3.pos()[2] << endl;
    os << "========================\n";
    return os;
}

int main(){

    Triangle *data;
    GPUMemory::alloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT,3,data);


    SHClipper clipper;
    clipper.execute();

    vector<PointObject> inPolygon;
    vector<Triangle> out;

    PointObject p;
    p.setPos(glm::vec4(-0.5f,-0.5f,0.0f,1.0f));
    inPolygon.push_back(p);

    p.setPos(glm::vec4(0.5f,-0.5f,0.0f,1.0f));
    p.setAttachInt("x",55555);
    inPolygon.push_back(p);


    p.setPos(glm::vec4(0.5f,0.5f,0.0f,1.0f));
    inPolygon.push_back(p);

    p.setPos(glm::vec4(glm::vec4(0.0f,0.0f,0.0f,1.0f)));
    p.setAttachInt("xx6",5);
    inPolygon.push_back(p);

    p.setPos(glm::vec4(glm::vec4(-0.5f,0.5f,0.0f,1.0f)));
    inPolygon.push_back(p);

//    inPolygon.push_back(glm::vec4(0.0f,0.5f,0.0f,1.0f));
//    inPolygon.push_back(glm::vec4(0.0f,-0.5f,0.0f,1.0f));
//    inPolygon.push_back(glm::vec4(2.0f,-0.5f,0.0f,1.0f));
//    inPolygon.push_back(glm::vec4(0.25f,0.0f,0.0f,1.0f));
//    inPolygon.push_back(glm::vec4(1.0f,0.5f,0.0f,1.0f));


    clipper.polygonToTriangle(inPolygon,out);

    for (int var = 0; var < out.size(); ++var) {
        cout << "Tri"<<var<<endl;
        cout << out.at(var);
    }

    cout << "2:"<<inPolygon[2].getAttachInt("xx6")<<endl;
    cout << "2:"<<inPolygon[2].getAttachInt("x")<<endl;
    cout << "3:"<<inPolygon[3].getAttachInt("xx6")<<endl;
    cout << "4:"<<inPolygon[4].getAttachInt("xx6")<<endl;
    cout << "4:"<<inPolygon[4].getAttachInt("x")<<endl;
    return 0;
}
