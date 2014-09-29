#include "core/culler.h"
#include "core/gpumemory.h"
#include "core/constant.h"
#include "core/primitive.h"

Culler::Culler()
{
}

void Culler::execute()
{
    int size;
    Triangle *data;
    if (!GPUMemory::retrieve<Triangle>(Constant::SF_CLIPOUT,size,data)){
        std::cerr << "retrieve Constant::SF_CLIPOUT failed" << std::endl;
        return;
    }

    // TODO: parallel
    for (int i = 0; i < size; ++i) {
        Triangle &tri = data[i];

        glm::vec3 normal = tri.normal();
        if (normal.z<=0) {
            tri.backFacing = true;
        }
        else {
            tri.backFacing = false;
        }
    }

}
