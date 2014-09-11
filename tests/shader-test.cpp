#include <iostream>

#include <core/vertexshader.h>
#include <core/gpumemory.h>
#include <core/pipeline.h>
#include <core/sutherlandhodgmanclipper.h>


using namespace std;

int main()
{
    VertexShader *vs = new VertexShader ;
    Clipper *cp = new SutherlandHodgmanClipper;
    PipeLine pl;
    pl.attachVertexShader(vs);
    pl.attachClipper(cp);
    pl.execute();

    glm::vec4 *data;
    int size;
    if (GPUMemory::retrieve<glm::vec4>("gl_position",size,data)) {
        for (int var = 0; var < size; ++var) {
            cout << data[var][0]<< endl;
            cout << data[var][1]<< endl;
            cout << data[var][2]<< endl;
            cout << data[var][3]<< endl;
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
