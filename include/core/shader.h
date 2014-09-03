#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>

#include <boost/any.hpp>

using std::string;
using std::map;
using boost::any;

class Shader
{
public:
    Shader();
    virtual ~Shader();

    virtual void initialize() = 0;
    virtual void execute() = 0;

    void setInputData(const string &, const any &);
    any getInputData(const string&);

private:
    map<string,any> m_inputData;
};

#endif // SHADER_H
