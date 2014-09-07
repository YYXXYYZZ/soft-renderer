#include <iostream>
#include <core/gpumemory.h>
#include <cassert>

using namespace std;

int main()
{

    int positions[] =
    {
        -1,-1,0,
        1,1,0,
        -1,1,0
    };

    int *a;
    GPUMemory::alloc<int>("int",9,a);
    GPUMemory::memoryCopy<int>("int",9,positions);

    int *data;
    int size;
    if (GPUMemory::retrieve<int>("int",size,data)) {
        for (int var = 0; var < size; ++var) {
            cout << data[var] << endl;
        }
    }

    GPUMemory::dealloc<int>("int");

    return 0;
}
