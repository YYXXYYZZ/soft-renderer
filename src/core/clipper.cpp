#include <core/clipper.h>
#include <core/gpumemory.h>
#include <core/constant.h>

Clipper::Clipper()
    :canClip(false)
{
}

void Clipper::initialize()
{
    if  (!GPUMemory::retrieve<Triangle>(Constant::SF_PRIMITIVESETUPOUT,primitiveCount,triangle)) {
        return;
    }
    canClip = true;
}

void Clipper::execute()
{
    initialize();
}


