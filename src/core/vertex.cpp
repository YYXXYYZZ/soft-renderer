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
{
    attach = new Attachment;
}

PointObject::~PointObject()
{
    delete attach;
}

PointObject &PointObject::operator=(const PointObject &other)
{
    attach->v_int = other.attach->v_int;
    attach->v_float = other.attach->v_float;
    attach->v_vec2 = other.attach->v_vec2;
    attach->v_vec3 = other.attach->v_vec3;
    attach->v_vec4 = other.attach->v_vec4;
}

void PointObject::setAttachInt(const std::string &name, const int &v)
{
    attach->v_int.insert(make_pair(name,v));
}

void PointObject::setAttachFloat(const std::string &name, const float &v)
{
    attach->v_float.insert(make_pair(name,v));
}

void PointObject::setAttachVec2(const std::string &name, const glm::vec2 &v)
{
    attach->v_vec2.insert(make_pair(name,v));
}

void PointObject::setAttachVec3(const std::string &name, const glm::vec3 &v)
{
    attach->v_vec3.insert(make_pair(name,v));
}

void PointObject::setAttachVec4(const std::string &name, const glm::vec4 &v)
{
    attach->v_vec4.insert(make_pair(name,v));
}

int PointObject::getAttachInt(const std::string &name)
{
    return attach->v_int[name];
}

float PointObject::getAttachFloat(const std::string &name)
{
    return attach->v_float[name];
}

glm::vec2 PointObject::getAttachVec2(const std::string &name)
{
    return attach->v_vec2[name];
}

glm::vec3 PointObject::getAttachVec3(const std::string &name)
{
    return attach->v_vec3[name];
}

glm::vec4 PointObject::getAttachVec4(const std::string &name)
{
    return attach->v_vec4[name];
}

PointObject PointObject::interpolate(const PointObject &v, float alpha) const
{
    assert(attach->v_int.size() == v.attach->v_int.size());
    assert(attach->v_float.size() == v.attach->v_float.size());
    assert(attach->v_vec2.size() == v.attach->v_vec2.size());
    assert(attach->v_vec3.size() == v.attach->v_vec3.size());
    assert(attach->v_vec4.size() == v.attach->v_vec4.size());

    PointObject result;

    for (auto i = attach->v_int.begin(); i != attach->v_int.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(attach->v_int.at(name),
                                        v.attach->v_int.at(name),
                                        alpha);
        result.setAttachInt(name,vaule);
    }

    for (auto i = attach->v_float.begin(); i != attach->v_float.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(attach->v_float.at(name),
                                        v.attach->v_float.at(name),
                                        alpha);
        result.setAttachFloat(name,vaule);
    }

    for (auto i = attach->v_vec2.begin(); i != attach->v_vec2.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(attach->v_vec2.at(name),
                                        v.attach->v_vec2.at(name),
                                        alpha);
        result.setAttachVec2(name,vaule);
    }

    for (auto i = attach->v_vec3.begin(); i != attach->v_vec3.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(attach->v_vec3.at(name),
                                        v.attach->v_vec3.at(name),
                                        alpha);
        result.setAttachVec3(name,vaule);
    }

    for (auto i = attach->v_vec4.begin(); i != attach->v_vec4.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(attach->v_vec4.at(name),
                                        v.attach->v_vec4.at(name),
                                        alpha);
        result.setAttachVec4(name,vaule);
    }

    return result;
}
