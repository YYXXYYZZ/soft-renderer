#include <iostream>

#include <core/vertexshader.h>
#include <core/gpumemory.h>
#include <core/pipeline.h>
#include <core/sutherlandhodgmanclipper.h>
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

int main()
{
    VertexShader *vs = new VertexShader ;
    Clipper *cp = new SutherlandHodgmanClipper;
    Pipeline pl;
    pl.attachVertexShader(vs);
    pl.attachClipper(cp);
    pl.render();


    Triangle *_data;
    int _size;
    if (GPUMemory::retrieve<Triangle>(Constant::SF_PRIMITIVESETUPOUT,_size,_data)) {
        for (int var = 0; var < _size; ++var) {
            cout << _data[var]<< endl;
        }
    }

    delete vs;
    delete cp;

    //    glm::vec4 a(0.0f,0.0f,0.0f,1.0f);
    //    glm::mat4 projection = glm::perspective(60.0f, (float)800/600, 0.3f, 100.0f);
    //    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,-1.0f),
    //                                 glm::vec3(0.0f,0.0f,0.0f),
    //                                 glm::vec3(0.0f,1.0f,0.0f));
    //    glm::mat4 MVP = projection*view;
    //    a= MVP *a;
    //    cout << "staring \n";
    //    cout << a[0]<< endl;
    //    cout << a[1]<< endl;
    //    cout << a[2]<< endl;
    //    cout << a[3]<< endl;


    return 0;
}
