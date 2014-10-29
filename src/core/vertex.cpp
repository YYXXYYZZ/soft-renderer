#include "core/vertex.h"
#include <cstring>

// TODO use Perspective-Correct Interpolation instead of
// linear interpolation
template<class T>
T interpolatePrivate(const T&v1,const T&v2,float &alpha)
{
    T r;
    r = T(v1*(1-alpha) +alpha*v2);
    return r;
}

template<class T>
T interpolatePrivate(const T&v1,const T&v2,const T&v3,float &alpha,float &beta)
{
    T r;
    r = T(v1*(1-alpha-beta) +alpha*v2 + beta*v3);
    return r;
}

template <>
vec2 interpolatePrivate<vec2>(const vec2&v1,const vec2&v2,float &alpha)
{
    vec2 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             alpha);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             alpha);
    return v;
}
template <>
vec2 interpolatePrivate(const vec2&v1,const vec2&v2,const vec2&v3,float &alpha,float &beta)
{
    vec2 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             v3.x,
                             alpha,
                             beta);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             v3.y,
                             alpha,
                             beta);
    return v;
}

template <>
vec3 interpolatePrivate<vec3>(const vec3&v1,const vec3&v2,float &alpha)
{
    vec3 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             alpha);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             alpha);
    v.z = interpolatePrivate(v1.z,
                             v2.z,
                             alpha);
    return v;
}

template <>
vec3 interpolatePrivate<vec3>(const vec3&v1,const vec3&v2,const vec3&v3,float &alpha,float &beta)
{
    vec3 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             v3.x,
                             alpha,
                             beta);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             v3.x,
                             alpha,
                             beta);
    v.z = interpolatePrivate(v1.z,
                             v2.z,
                             v3.x,
                             alpha,
                             beta);
    return v;
}

template <>
vec4 interpolatePrivate<vec4>(const vec4&v1,const vec4&v2,float &alpha)
{
    vec4 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             alpha);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             alpha);
    v.z = interpolatePrivate(v1.z,
                             v2.z,
                             alpha);
    v.w = interpolatePrivate(v1.w,
                             v2.w,
                             alpha);
    return v;
}

template <>
vec4 interpolatePrivate<vec4>(const vec4&v1,const vec4&v2,const vec4&v3,float &alpha,float &beta)
{
    vec4 v;
    v.x = interpolatePrivate(v1.x,
                             v2.x,
                             v3.x,
                             alpha,
                             beta);
    v.y = interpolatePrivate(v1.y,
                             v2.y,
                             v3.x,
                             alpha,
                             beta);
    v.z = interpolatePrivate(v1.z,
                             v2.z,
                             v3.x,
                             alpha,
                             beta);
    v.w = interpolatePrivate(v1.w,
                             v2.w,
                             v3.x,
                             alpha,
                             beta);
    return v;
}



PointObject::PointObject()
    :p_attach(new Attachment)
{
}

PointObject::~PointObject()
{
    if(p_attach.use_count()==0)
        delete p_attach.get();
}

PointObject::PointObject(const PointObject &other)
{
    p_attach = other.p_attach;
    x = other.x;
    y = other.y;
    w = other.w;
    z = other.z;


}

PointObject &PointObject::operator=(const PointObject &other)
{
    p_attach = other.p_attach;
    x = other.x;
    y = other.y;
    w = other.w;
    z = other.z;
    return *this;
}

bool PointObject::operator!=(const PointObject &other)
{
    return getPos()!=other.getPos();
}

PointObject &PointObject::operator/(float scale)
{
    this->x /= scale;
    this->y /= scale;
    this->z /= scale;
    this->w /= scale;
    return *this;
}

void PointObject::setAttachInt(const std::string &name, const int &v)
{
    detach();
    p_attach->v_int.insert(make_pair(name,v));
}

void PointObject::setAttachFloat(const std::string &name, const float &v)
{
    detach();
    p_attach->v_float.insert(make_pair(name,v));
}

void PointObject::setAttachVec2(const std::string &name, const glm::vec2 &v)
{
    detach();
    p_attach->v_vec2.insert(make_pair(name,v));
}

void PointObject::setAttachVec3(const std::string &name, const glm::vec3 &v)
{
    detach();
    p_attach->v_vec3.insert(make_pair(name,v));
}

void PointObject::setAttachVec4(const std::string &name, const glm::vec4 &v)
{
    detach();
    p_attach->v_vec4.insert(make_pair(name,v));
}

int PointObject::getAttachInt(const std::string &name) const
{
    return p_attach->v_int[name];
}

float PointObject::getAttachFloat(const std::string &name) const
{
    return p_attach->v_float[name];
}

glm::vec2 PointObject::getAttachVec2(const std::string &name) const
{
    return p_attach->v_vec2[name];
}

glm::vec3 PointObject::getAttachVec3(const std::string &name) const
{
    return p_attach->v_vec3[name];
}

glm::vec4 PointObject::getAttachVec4(const std::string &name) const
{
    return p_attach->v_vec4[name];
}

void PointObject::interpolate(const PointObject &v1,
                              const PointObject &v2,
                              PointObject &out, float alpha)
{
    assert(v1.p_attach->v_int.size() == v2.p_attach->v_int.size());
    assert(v1.p_attach->v_float.size() == v2.p_attach->v_float.size());
    assert(v1.p_attach->v_vec2.size() == v2.p_attach->v_vec2.size());
    assert(v1.p_attach->v_vec3.size() == v2.p_attach->v_vec3.size());
    assert(v1.p_attach->v_vec4.size() == v2.p_attach->v_vec4.size());

    out.p_attach = shared_ptr<Attachment>(new Attachment);

    for (auto i = v1.p_attach->v_int.begin(); i != v1.p_attach->v_int.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_int.at(name),
                                        v2.p_attach->v_int.at(name),
                                        alpha);
        out.setAttachInt(name,vaule);
    }

    for (auto i = v1.p_attach->v_float.begin(); i != v1.p_attach->v_float.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_float.at(name),
                                        v2.p_attach->v_float.at(name),
                                        alpha);
        out.setAttachFloat(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec2.begin(); i !=v1.p_attach->v_vec2.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec2.at(name),
                                        v2.p_attach->v_vec2.at(name),
                                        alpha);
        out.setAttachVec2(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec3.begin(); i != v1.p_attach->v_vec3.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec3.at(name),
                                        v2.p_attach->v_vec3.at(name),
                                        alpha);
        out.setAttachVec3(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec4.begin(); i != v1.p_attach->v_vec4.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec4.at(name),
                                        v2.p_attach->v_vec4.at(name),
                                        alpha);
        out.setAttachVec4(name,vaule);
    }
}

void PointObject::interpolate(const PointObject &v1,
                              const PointObject &v2,
                              const PointObject &v3,
                              PointObject &out,
                              float &alpha,
                              float &beta)
{

    // no assert ?
    assert(v1.p_attach->v_int.size() == v2.p_attach->v_int.size());
    assert(v1.p_attach->v_float.size() == v2.p_attach->v_float.size());
    assert(v1.p_attach->v_vec2.size() == v2.p_attach->v_vec2.size());
    assert(v1.p_attach->v_vec3.size() == v2.p_attach->v_vec3.size());
    assert(v1.p_attach->v_vec4.size() == v2.p_attach->v_vec4.size());

    out.p_attach = shared_ptr<Attachment>(new Attachment);

    for (auto i = v1.p_attach->v_int.begin(); i != v1.p_attach->v_int.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_int.at(name),
                                        v2.p_attach->v_int.at(name),
                                        v3.p_attach->v_int.at(name),
                                        alpha,
                                        beta);
        out.setAttachInt(name,vaule);
    }

    for (auto i = v1.p_attach->v_float.begin(); i != v1.p_attach->v_float.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_float.at(name),
                                        v2.p_attach->v_float.at(name),
                                        v3.p_attach->v_float.at(name),
                                        alpha,
                                        beta);
        out.setAttachFloat(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec2.begin(); i !=v1.p_attach->v_vec2.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec2.at(name),
                                        v2.p_attach->v_vec2.at(name),
                                        v3.p_attach->v_vec2.at(name),
                                        alpha,
                                        beta);
        out.setAttachVec2(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec3.begin(); i != v1.p_attach->v_vec3.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec3.at(name),
                                        v2.p_attach->v_vec3.at(name),
                                        v3.p_attach->v_vec3.at(name),
                                        alpha,
                                        beta);
        out.setAttachVec3(name,vaule);
    }

    for (auto i = v1.p_attach->v_vec4.begin(); i != v1.p_attach->v_vec4.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v1.p_attach->v_vec4.at(name),
                                        v2.p_attach->v_vec4.at(name),
                                        v3.p_attach->v_vec4.at(name),
                                        alpha,
                                        beta);
        out.setAttachVec4(name,vaule);
    }

}

void PointObject::setPos(const glm::vec4 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

glm::vec4 PointObject::getPos() const
{
    return vec4(x,y,z,w);
}

float PointObject::distanceTo(const PointObject &other)
{
    return sqrtf((x-other.x)*(x-other.x) +
                 (y-other.y)*(y-other.y) +
                 (z-other.z)*(z-other.z));
}

void PointObject::detach()
{
    // if shared_ptr is unique and assign a new
    // pointer to it, the old one will be deleted.
    auto other = *p_attach;
    p_attach = shared_ptr<Attachment>(new Attachment);
    p_attach->v_int = other.v_int;
    p_attach->v_float = other.v_float;
    p_attach->v_vec2 = other.v_vec2;
    p_attach->v_vec3 = other.v_vec3;
    p_attach->v_vec4 = other.v_vec4;
}
