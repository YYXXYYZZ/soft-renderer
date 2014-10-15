#include "core/vertex.h"
#include <cstring>

template<class T>
T interpolatePrivate(const T&v1,const T&v2,float alpha)
{
    T r;
    r = v1 + alpha * (v2-v1);
    return r;
}

template <>
vec2 interpolatePrivate<vec2>(const vec2&v1,const vec2&v2,float alpha)
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
vec3 interpolatePrivate<vec3>(const vec3&v1,const vec3&v2,float alpha)
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
vec4 interpolatePrivate<vec4>(const vec4&v1,const vec4&v2,float alpha)
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

PointObject PointObject::interpolate(const PointObject &v, float alpha) const
{
    assert(p_attach->v_int.size() == v.p_attach->v_int.size());
    assert(p_attach->v_float.size() == v.p_attach->v_float.size());
    assert(p_attach->v_vec2.size() == v.p_attach->v_vec2.size());
    assert(p_attach->v_vec3.size() == v.p_attach->v_vec3.size());
    assert(p_attach->v_vec4.size() == v.p_attach->v_vec4.size());

    PointObject result;

    for (auto i = p_attach->v_int.begin(); i != p_attach->v_int.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(p_attach->v_int.at(name),
                                        v.p_attach->v_int.at(name),
                                        alpha);
        result.setAttachInt(name,vaule);
    }

    for (auto i = p_attach->v_float.begin(); i != p_attach->v_float.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(p_attach->v_float.at(name),
                                        v.p_attach->v_float.at(name),
                                        alpha);
        result.setAttachFloat(name,vaule);
    }

    for (auto i = p_attach->v_vec2.begin(); i != p_attach->v_vec2.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(p_attach->v_vec2.at(name),
                                        v.p_attach->v_vec2.at(name),
                                        alpha);
        result.setAttachVec2(name,vaule);
    }

    for (auto i = p_attach->v_vec3.begin(); i != p_attach->v_vec3.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(p_attach->v_vec3.at(name),
                                        v.p_attach->v_vec3.at(name),
                                        alpha);
        result.setAttachVec3(name,vaule);
    }

    for (auto i = p_attach->v_vec4.begin(); i != p_attach->v_vec4.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(p_attach->v_vec4.at(name),
                                        v.p_attach->v_vec4.at(name),
                                        alpha);
        result.setAttachVec4(name,vaule);
    }

    return result;
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

void PointObject::detach()
{
    auto other = p_attach.get();
    p_attach = shared_ptr<Attachment>(new Attachment);
    p_attach->v_int = other->v_int;
    p_attach->v_float = other->v_float;
    p_attach->v_vec2 = other->v_vec2;
    p_attach->v_vec3 = other->v_vec3;
    p_attach->v_vec4 = other->v_vec4;
}
