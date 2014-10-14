#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using std::vector;
using std::string;
using std::map;


class Attachment{
private:
    map<string,int> v_int;
    map<string,float> v_float;
    map<string,vec2> v_vec2;
    map<string,vec3> v_vec3;
    map<string,vec4> v_vec4;

    Attachment operator=(const Attachment&);

public:
    Attachment() =default;
    ~Attachment() =default;
    void addInt(const string &name,const int&v);
    void addFloat(const string &name,const float&v);
    void addVec2(const string &name,const vec2&v);
    void addVec3(const string &name,const vec3&v);
    void addVec4(const string &name,const vec4&v);

    Attachment *interpolate(Attachment *v,float alpha);
};


struct Vertex
{
    glm::vec4 pos;
    Attachment *attach;
};

#endif // VERTEX_H
