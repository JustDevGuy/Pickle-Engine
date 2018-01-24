#ifndef SHADERSOURCE_H
#define SHADERSOURCE_H

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class ShaderSource
{
public:
    ShaderSource(std::string vertexFile, std::string fragmentFile);
    void Start();
    void Stop();
    void CleanUp();
private:
    const char *ReadFile(std::string fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

    GLuint vertexShader, fragmentShader;
    GLuint program;
protected:
    void BindAttributeLocation(int location, std::string variableName);
    int GetUniformLocation(std::string uniformName);

    void LoadFloat(int location, float value);
    void LoadVector(int location, glm::vec3 value);
    void LoadBoolean(int location, bool value);
    void LoadMatrix(int location, glm::mat4 value);
};

#endif // SHADERSOURCE_H
