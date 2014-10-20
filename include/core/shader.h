#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    Shader();
    virtual ~Shader();

    virtual void execute();
    void setIntializeFuction(void (*initialize)());

protected:
    void (*initialize)();

};

#endif // SHADER_H
