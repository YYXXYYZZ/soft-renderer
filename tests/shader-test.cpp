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

    return 0;
}
