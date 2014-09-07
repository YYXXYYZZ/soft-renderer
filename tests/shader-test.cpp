#include <iostream>

#include <core/vertexshader.h>
#include <core/gpumemory.h>
#include <core/pipeline.h>

using namespace std;

int main()
{
    VertexShader *vs = new VertexShader ;
    PipeLine pl;
    pl.attachVertexShader(vs);
    pl.execute();

    float *data;
    int size;
    if (GPUMemory::retrieve<float>("out",size,data)) {
        for (int var = 0; var < size; ++var) {
            cout << data[var] << endl;
        }
    }

    return 0;
}
