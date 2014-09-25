#include <core/primitive.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <iostream>
#include <vector>

using std::vector;
using glm::vec4;

Primitive::Primitive()
{
}

bool Primitive::setup(PrimitiveType type, int count)
{
    bool error = GPUMemory::retrieve<vec4>(Constant::SF_POSITION,positionSize,positionData);
    if(!error){
        std::cerr << "Retrieve sf_position failed!\n";
        return true;
    }

    switch (type) {
    case TRIANGLES:{
        Triangle* objects;
        int size = count < positionSize ? count : positionSize;
        size = size/3;

        GPUMemory::alloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT,size,objects);
        //TODO
        for (int i = 0; i < size; i++) {
            objects[i].p1 = positionData[i*3];
            objects[i].p2 = positionData[i*3+1];
            objects[i].p3 = positionData[i*3+2];
        }
    }
        break;
    default:
        break;
    }

    return true;
}

bool Primitive::setupByIndex(PrimitiveType type, int count)
{
    bool error = GPUMemory::retrieve<glm::vec4>(Constant::SF_POSITION,positionSize,positionData);
    if(!error){
        std::cerr << "Retrieve sf_position failed!\n";
        return false;
    }
    error = GPUMemory::retrieve<int>(Constant::SF_POSITIONINDEX,indexSize,indexData);
    if(!error){
        std::cerr << "Retrieve sf_position_index failed!\n";
        return false;
    }


    return true;
}
