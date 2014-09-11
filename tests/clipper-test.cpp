#include <iostream>
#include <core/sutherlandhodgmanclipper.h>
#include <core/gpumemory.h>


int main(){

    glm::vec4 *data;
    GPUMemory::alloc<glm::vec4>("gl_position",3,data);
    data[0] = glm::vec4(0.0f,1.5f,0.0f,1.0f);
    data[1] = glm::vec4(-1.0f,0.0f,1.0f,1.0f);
    data[2] = glm::vec4(1.0f,0.0f,2.0f,1.0f);

    SutherlandHodgmanClipper clipper;
    clipper.execute();

    return 0;
}
