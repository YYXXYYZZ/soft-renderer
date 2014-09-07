#include <iostream>
#include <core/global.h>

using namespace std;

int main()
{
    extern GPUMemory GlobalGPUMemory;
    GlobalGPUMemory.alloc("_int_",1000,Int);
    GlobalGPUMemory.alloc("_int_",1000,Int);
    GlobalGPUMemory.dealloc("_wwwwwwwwww_");
//    GlobalGPUMemory.dealloc("_int_");

    MemoryInfo info;
    bool success;
    success = GlobalGPUMemory.retrieve("_int_",info);
    cout<<success <<endl;


    return 0;
}
