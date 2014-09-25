#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <glm/glm.hpp>

using glm::vec4;
using glm::vec3;

enum PrimitiveType{
    POINTS,
    LINES,LINESTRIP,LINElOOP,
    TRIANGLES,TRIANGLEFAN
};

struct Point{
    vec4 p1;
};

struct Line{
    vec4 p1;
    vec4 p2;
};

struct Triangle{
    vec4 p1;
    vec4 p2;
    vec4 p3;

    bool inside(const vec4&p) const{
        /*
         * http://www.cnblogs.com/graphics/archive/2010/08/05/1793393.html
         * 所以对于平面内任意一点，都可以由如下方程来表示P = A +  u * (C – A) + v * (B - A) // 方程1
         * 如果系数u或v为负值，那么相当于朝相反的方向移动，即BA或CA方向。那么如果想让P位于三角形ABC内部，u和v必须满足什么条件呢？有如下三个条件
         * u >= 0
         * v >= 0
         * u + v <= 1
         * 几个边界情况，当u = 0且v = 0时，就是点A，当u = 0,v = 1时，就是点B，而当u = 1, v = 0时，就是点C
         * 整理方程1得到P – A = u(C - A) + v(B - A)
         * 令v0 = C – A, v1 = B – A, v2 = P – A，则v2 = u * v0 + v * v1，现在是一个方程，两个未知数，无法解出u和v，将等式两边分别点乘v0和v1的到两个等式
         * (v2) • v0 = (u * v0 + v * v1) • v0
         * (v2) • v1 = (u * v0 + v * v1) • v1
         * 注意到这里u和v是数，而v0，v1和v2是向量，所以可以将点积展开得到下面的式子。
         * v2 • v0 = u * (v0 • v0) + v * (v1 • v0)  // 式1
         * v2 • v1 = u * (v0 • v1) + v * (v1• v1)   // 式2
         * 解这个方程得到
         * u = ((v1•v1)(v2•v0)-(v1•v0)(v2•v1)) / ((v0•v0)(v1•v1) - (v0•v1)(v1•v0))
         * v = ((v0•v0)(v2•v1)-(v0•v1)(v2•v0)) / ((v0•v0)(v1•v1) - (v0•v1)(v1•v0))
         */

        vec3 v0(p3 - p1);
        vec3 v1(p2 - p1);
        vec3 v2(p - p1);

        float dot00 = glm::dot(v0,v0);
        float dot01 = glm::dot(v0,v1);
        float dot02 = glm::dot(v0,v2);
        float dot11 = glm::dot(v1,v1);
        float dot12 = glm::dot(v1,v2);

        float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

        float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
        // if u out of range, return directly
        if (u < 0 || u > 1)
        {
            return false ;
        }

        float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
        // if v out of range, return directly
        if (v < 0 || v > 1)
        {
            return false ;
        }
        return u + v <= 1 ;
    }
};

class Primitive
{
public:
    Primitive();
    bool setup(PrimitiveType type,int count);
    bool setupByIndex(PrimitiveType type,int count);

private:
    int positionSize;
    vec4 *positionData;
    int indexSize;
    int *indexData;
};

#endif // PRIMITIVE_H
