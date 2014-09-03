#include <iostream>

#include "shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{


}

void Shader::setInputData(const std::string &key, const boost::any &value)
{
    m_inputData.insert(std::pair<string,any>(key,value));
}

boost::any Shader::getInputData(const std::string & key)
{
    boost::any value = m_inputData[key];
    if(value.empty()){
        std::cerr << "Warning: try to index a none exist key" <<key << std::endl;
    }
    return value;
}
