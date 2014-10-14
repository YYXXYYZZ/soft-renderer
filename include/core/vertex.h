#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <string>
#include <map>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using std::map;
using std::string;

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
    PointObject &operator=(const PointObject&other);

    vec4 pos;

    // attachment
    void setAttachInt(const string &name,const int&v);
    void setAttachFloat(const string &name,const float&v);
    void setAttachVec2(const string &name,const vec2&v);
    void setAttachVec3(const string &name,const vec3&v);
    void setAttachVec4(const string &name,const vec4&v);

    int getAttachInt(const string &name);
    float getAttachFloat(const string &name);
    vec2 getAttachVec2(const string &name);
    vec3 getAttachVec3(const string &name);
    vec4 getAttachVec4(const string &name);

    PointObject interpolate(const PointObject &v, float alpha) const;

private:
    Attachment *attach;
};

#endif // VERTEX_H
