#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using std::map;
using std::string;
using std::shared_ptr;


struct Triangle;

struct Attachment{
    map<string,int> v_int;
    map<string,float> v_float;
    map<string,vec2> v_vec2;
    map<string,vec3> v_vec3;
    map<string,vec4> v_vec4;

};

class PointObject
{
public:
    PointObject();
    ~PointObject();
    PointObject(const PointObject&other);
    PointObject &operator=(const PointObject&other);
    bool operator!=(const PointObject&other);
    PointObject &operator/(float scale);

    // attachment
    void setAttachInt(const string &name,const int&v);
    void setAttachFloat(const string &name,const float&v);
    void setAttachVec2(const string &name,const vec2&v);
    void setAttachVec3(const string &name,const vec3&v);
    void setAttachVec4(const string &name,const vec4&v);

    int getAttachInt(const string &name) const;
    float getAttachFloat(const string &name) const;
    vec2 getAttachVec2(const string &name) const;
    vec3 getAttachVec3(const string &name) const;
    vec4 getAttachVec4(const string &name) const;

    static void interpolate(const PointObject &v1,
                            const PointObject &v2,
                            PointObject &out,
                            float alpha);

    static void interpolate(const PointObject &v1,
                            const PointObject &v2,
                            const PointObject &v3,
                            PointObject &out,
                            float &alpha,
                            float &beta);

   static void interpolate(PointObject &p,const Triangle&t);


    void setPos(const vec4&v);
    vec4 pos() const;

    float distanceTo(const PointObject &other);

private:
    shared_ptr<Attachment> p_attach;
    void detach();

public:
    float x;
    float y;
    float z;
    float w;
};

#endif // VERTEX_H
