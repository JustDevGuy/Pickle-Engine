#ifndef STATICSHADER_H_INCLUDED
#define STATICSHADER_H_INCLUDED

#include "ShaderSource.h"

class StaticShader : public ShaderSource
{
public:
    StaticShader() : ShaderSource(".//res//shaders//vertexShader.glsl", ".//res//shaders//fragmentShader.glsl")
    {
    }

    void UseReflection(bool value)
    {
        LoadBoolean(location_useReflection, value);
    }

    void UseFakeLighting(bool value) //Doesn't use light
    {
        LoadBoolean(location_useFakeLight, value);
    }

    void LoadLight(glm::vec3 lightPosition) //Light
    {
        LoadVector(location_lightPosition, lightPosition);
    }

    void LoadTransformationMatrix(glm::mat4 matrix) //Position, rotation and scale of model
    {
        LoadMatrix(location_transformationMatrix, matrix);
    }

    void LoadViewMatrix(glm::mat4 viewMatrix) //Camera perspective and etc
    {
        LoadMatrix(location_viewMatrix, viewMatrix);
    }
private:
    const int location_transformationMatrix = GetUniformLocation("transform");
    const int location_viewMatrix = GetUniformLocation("view");
    const int location_lightPosition = GetUniformLocation("lightPosition");
    const int location_useFakeLight = GetUniformLocation("useFakeLighting");
    const int location_useReflection = GetUniformLocation("useReflection");
};

#endif // STATICSHADER_H_INCLUDED
