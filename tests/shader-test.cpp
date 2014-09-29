#include <iostream>

#include <core/vertexshader.h>
#include <core/gpumemory.h>
#include <core/pipeline.h>
#include <core/constant.h>
#include <glm/glm.hpp>

using namespace std;

ostream & operator <<(ostream &os,const Triangle &t){

    os << "========================\n";
    os << t.p1[0] <<" " << t.p1[1] << " " << t.p1[2] << endl;
    os << t.p2[0] <<" " << t.p2[1] << " " << t.p2[2] << endl;
    os << t.p3[0] <<" " << t.p3[1] << " " << t.p3[2] << endl;
    os << "========================\n";
    return os;
}

ostream & operator <<(ostream &os,const glm::vec4 &t){

    os << "=================================\n";
    os << "x: " << t.x << " y: " << t.y << " z: " << t.z << " w: " << t.w << endl;
    os << "=================================\n";
    return os;
}

int main()
{
    VertexShader *vs = new VertexShader ;
    Pipeline pl;
    pl.attachVertShader(vs);
    pl.render();


//    Triangle *_data;
//    int _size;
//    if (GPUMemory::retrieve<Triangle>(Constant::SF_PRIMITIVESETUPOUT,_size,_data)) {
//        for (int var = 0; var < _size; ++var) {
//            cout << _data[var]<< endl;
//        }
//    }.

    glm::vec4 *_data;
    int _size;
    if (GPUMemory::retrieve<glm::vec4>(Constant::SF_CLIPOUT,_size,_data)) {
        for (int var = 0; var < _size; ++var) {
            cout << _data[var]<< endl;
        }
    }

    delete vs;


    return 0;
}
