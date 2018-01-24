#ifndef STATICSHADER_H_INCLUDED
#define STATICSHADER_H_INCLUDED

#include "ShaderSource.h"

class StaticShader : public ShaderSource
{
public:
    // Load shaders
    StaticShader() : ShaderSource(".//res//shaders//vertexShader.glsl", ".//res//shaders//fragmentShader.glsl")
    {
    }

    // Set if model gonna reflect light
    void UseReflection(bool value)
    {
        LoadBoolean(location_useReflection, value);
    }

    // Model not need light
    void UseFakeLighting(bool value)
    {
        LoadBoolean(location_useFakeLight, value);
    }

    // Load a light position
    void LoadLight(glm::vec3 lightPosition)
    {
        LoadVector(location_lightPosition, lightPosition);
    }

    // Load the entity transform
    void LoadTransformationMatrix(glm::mat4 matrix)
    {
        LoadMatrix(location_transformationMatrix, matrix);
    }

    // Load the camera matrix
    void LoadViewMatrix(glm::mat4 viewMatrix)
    {
        LoadMatrix(location_viewMatrix, viewMatrix);
    }
private:
    // Uniform variables location
    const int location_transformationMatrix = GetUniformLocation("transform");
    const int location_viewMatrix = GetUniformLocation("view");
    const int location_lightPosition = GetUniformLocation("lightPosition");
    const int location_useFakeLight = GetUniformLocation("useFakeLighting");
    const int location_useReflection = GetUniformLocation("useReflection");
};

#endif // STATICSHADER_H_INCLUDED
