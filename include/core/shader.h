#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    Shader();
    virtual ~Shader();

    // initialize will init all necessary memory and uniform variable
    // iterationTimes will return how many times iterationCompute will
    // calld. iterationCompute should be called paralleled which will
    // simulate main function in shader.
    void execute();

    bool getReinitialize() const;
    void setReinitialize(bool value);

protected:
    virtual void initialize() = 0;
    virtual int iterationTimes() = 0;
    virtual void iterationCompute(int step) = 0;

private:
    bool reinitialize;

};

#endif // SHADER_H