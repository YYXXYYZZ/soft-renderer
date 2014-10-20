#include <iostream>
#include "core/shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{

}

void Shader::execute()
{

}

void Shader::setIntializeFuction(void (*initialize)())
{
    this->initialize = initialize;
}
