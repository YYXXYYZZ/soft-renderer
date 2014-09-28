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
        std::cerr << "culler::execute\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        Triangle &tri = data[i];
//        float a;
//        a =     (tri.p2.y+tri.p1.y)*(tri.p2.x-tri.p1.x)+
//                (tri.p3.y+tri.p2.y)*(tri.p3.x-tri.p2.x)+
//                (tri.p1.y+tri.p3.y)*(tri.p1.x-tri.p3.x);
//        a /= 2.0f;

//        if (a<0) {
//            tri.backFacing = false;
//        }
        glm::vec3 v1(tri.p2-tri.p1);
        glm::vec3 v2(tri.p3-tri.p1);
        glm::vec3 n = glm::cross(v1,v2);
        if (n.z<=0) {
            tri.backFacing = true;
        }
        else {
            tri.backFacing = false;
        }

    }

}
