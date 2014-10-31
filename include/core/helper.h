#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace helper {

static std::vector<glm::vec3> vertices;
static std::vector<glm::vec3> colors;
static std::vector<int> faces;

glm::vec3 splitToVec3(const string & str){
    vector<float> vs;
    size_t pos=0,old=0;
    pos = str.find_first_of(" ",pos);
    while(pos!=string::npos){
        string value = str.substr(old,pos-old);
        old = pos+1;
        pos = str.find_first_of(" ",old);
        float v = ::atof(value.c_str());
        vs.push_back(v);
    }
    string value = str.substr(old,str.size()-old);
    float v = ::atof(value.c_str());
    vs.push_back(v);
    if(vs.size()>3){
        std::cerr << "Wrong fomat of vector" << str <<std::endl;
        return glm::vec3();
    }

    return glm::vec3(vs[0],vs[1],vs[2]);

}

void splitToface(const string &str){
    size_t pos=0,old=0;
    pos = str.find_first_of(" ",pos);
    while(pos!=string::npos){
        string value = str.substr(old,pos-old);
        old = pos+1;
        pos = str.find_first_of(" ",old);
        int v = ::atoi(value.c_str())-1;
        faces.push_back(v);
    }
    string value = str.substr(old,str.size()-old);
    int v = ::atoi(value.c_str())-1;
    faces.push_back(v);
}

static char* readSource(const char* file)
{
    FILE* fp = fopen(file, "r");

    if ( fp == NULL ) { return NULL; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}



void loadObj(const char* file)
{
    const char *data = readSource(file);
    if(!data){
        std::cerr << "Can not open obj file"<< std::endl;
        exit(-1);
        return;
    }
    //clear old data
    vertices.clear();
    colors.clear();
    faces.clear();

    string buf(data);
    size_t pos=0,old=0;
    pos = buf.find_first_of("\r\n",pos);
    while(pos!=string::npos){
        string line = buf.substr(old,pos-old);

        static int count = 0;
        count++;

        if(count == 139119)
            count = count;

        old = pos+1;
        pos = buf.find_first_of("\r\n",old);

        if(line.size()<2){
            break; //empty or broken line
        }
        string firstWord = line.substr(0,2);

        if(firstWord.compare("v ")==0){
            string values = line.substr(2,line.size()-2);
            vertices.push_back(splitToVec3(values));
        }
        else if(firstWord.compare("vc")==0){
            string values = line.substr(3,line.size()-2);
            colors.push_back(splitToVec3(values));
        }
        else if(firstWord.compare("f ")==0){
            string values = line.substr(2,line.size()-2);
            if(values == "16684 16744 16743")
                values = values;
            splitToface(values);
        }

    }

}
}
