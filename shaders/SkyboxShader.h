#ifndef SKYBOXSHADER_H_INCLUDED
#define SKYBOXSHADER_H_INCLUDED

#include "../render/ShaderSource.h"

class SkyboxShader : public ShaderSource
{
public:
    // Load shaders
    SkyboxShader() : ShaderSource(".//res//shaders//skyboxVertex.glsl", ".//res//shaders//skyboxFragment.glsl")
    {
    }

    // Load the position of the skybox to shader
    void LoadTransformationMatrix(glm::mat4 matrix)
    {
        LoadMatrix(location_transformationMatrix, matrix);
    }

    // Show the skybox in the camera
    void LoadViewMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
    {
        viewMatrix[3][0] = 0;
        viewMatrix[3][1] = 0;
        viewMatrix[3][2] = 0;
        LoadMatrix(location_viewMatrix, viewMatrix);
        LoadMatrix(location_projectionMatrix, projectionMatrix);
    }
private:
    // Uniform variables locations
    const int location_transformationMatrix = GetUniformLocation("transform");
    const int location_lightDirection = GetUniformLocation("lightDirection");
    const int location_viewMatrix = GetUniformLocation("viewMatrix");
    const int location_projectionMatrix = GetUniformLocation("projectionMatrix");
};

#endif // SKYBOXSHADER_H_INCLUDED
