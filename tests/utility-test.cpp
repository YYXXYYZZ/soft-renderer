#include <iostream>
#include <core/primitive.h>

using namespace std;
ostream & operator <<(ostream &os,const Triangle &t){

    os << "========================\n";
    os << t.p1.pos()[0] <<" " << t.p1.pos()[1] << " " << t.p1.pos()[2] << endl;
    os << t.p2.pos()[0] <<" " << t.p2.pos()[1] << " " << t.p2.pos()[2] << endl;
    os << t.p3.pos()[0] <<" " << t.p3.pos()[1] << " " << t.p3.pos()[2] << endl;
    os << "========================\n";
    return os;
}

int main()
{
//    Triangle *t;
//    t = new Triangle;
//    t->p1.getPos() = glm::vec4(-0.5f,0.0f,0.0f,1.0f);
//    t->p2.getPos() = glm::vec4(1.0f,0.5f,0.0f,1.0f);
//    t->p3.getPos() = glm::vec4(0.0f,-0.5f,0.0f,1.0f);

//    t->p1.setAttachFloat("f",1.2f);

//    vec2 min;
//    vec2 max;
//    std::set<float> result;
//    t->extremeValue(min,max);
//    t->intersect(0.5f,min.x,max.x,result);

//    for (auto iter = result.begin(); iter != result.end(); ++iter) {
//        cout << *iter << endl;
//    }

//    Triangle *f;
//    f = new Triangle;
//    *f = *t;


//    Triangle &q = *t;



//    delete t;
//    f->backFacing;
//    f->normal();
//    std::cout <<"f.p1:"<<f->p1.getAttachFloat("f") << std::endl;
//    delete f;



//    q.normal();
    PointObject *p = new PointObject;
    p->setAttachFloat("f",1.2f);

    PointObject &f = *p;

    p->setAttachFloat("f",2.0f);
    f.setAttachFloat("x",2.0f);

    std::cout <<"f:" << f.getAttachFloat("x") << std::endl;

    return 0;
}
