#include "core/vertex.h"


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


void Attachment::addInt(const std::string &name, const int &v)
{
    v_int.insert(make_pair(name,v));
}

void Attachment::addFloat(const std::string &name, const float &v)
{
    v_float.insert(make_pair(name,v));
}

void Attachment::addVec2(const std::string &name, const glm::vec2 &v)
{
    v_vec2.insert(make_pair(name,v));
}

void Attachment::addVec3(const std::string &name, const glm::vec3 &v)
{
    v_vec3.insert(make_pair(name,v));
}

void Attachment::addVec4(const std::string &name, const glm::vec4 &v)
{
    v_vec4.insert(make_pair(name,v));
}

Attachment *Attachment::interpolate(Attachment *v, float alpha)
{

    assert(v_int.size() == v->v_int.size());
    assert(v_float.size() == v->v_float.size());
    assert(v_vec2.size() == v->v_vec2.size());
    assert(v_vec3.size() == v->v_vec3.size());
    assert(v_vec4.size() == v->v_vec4.size());

    Attachment *result = new Attachment;

    for (auto i = v_int.begin(); i != v_int.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v_int.at(name),
                                    v->v_int.at(name),
                                    alpha);
        result->addInt(name,vaule);
    }

    for (auto i = v_float.begin(); i != v_float.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v_float.at(name),
                                    v->v_float.at(name),
                                    alpha);
        result->addFloat(name,vaule);
    }

    for (auto i = v_vec2.begin(); i != v_vec2.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v_vec2.at(name),
                                    v->v_vec2.at(name),
                                    alpha);
        result->addVec2(name,vaule);
    }

    for (auto i = v_vec3.begin(); i != v_vec3.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v_vec3.at(name),
                                    v->v_vec3.at(name),
                                    alpha);
        result->addVec3(name,vaule);
    }

    for (auto i = v_vec4.begin(); i != v_vec4.end(); ++i) {
        string name = i->first;
        auto vaule = interpolatePrivate(v_vec4.at(name),
                                    v->v_vec4.at(name),
                                    alpha);
        result->addVec4(name,vaule);
    }

    return result;
}
