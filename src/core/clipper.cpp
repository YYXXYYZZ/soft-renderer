#include <core/clipper.h>
#include <core/gpumemory.h>

Clipper::Clipper()
    :canClip(false)
{
}

void Clipper::initialize()
{
    if  (!GPUMemory::retrieve<glm::vec4>("gl_position",size,position)) {
        return;
    }
    canClip = true;
}

void Clipper::execute()
{
    initialize();

}


