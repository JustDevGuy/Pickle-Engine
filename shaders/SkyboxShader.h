#ifndef SKYBOXSHADER_H_INCLUDED
#define SKYBOXSHADER_H_INCLUDED

#include "../render/ShaderSource.h"

class SkyboxShader : public ShaderSource
{
public:
    SkyboxShader() : ShaderSource(".//res//shaders//skyboxVertex.glsl", ".//res//shaders//skyboxFragment.glsl")
    {
    }

    void LoadTransformationMatrix(glm::mat4 matrix) //Translate, rotate and scale of model
    {
        LoadMatrix(location_transformationMatrix, matrix);
    }

    void LoadViewMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) //Camera perspective and etc
    {
        viewMatrix[3][0] = 0;
        viewMatrix[3][1] = 0;
        viewMatrix[3][2] = 0;
        LoadMatrix(location_viewMatrix, viewMatrix);
        LoadMatrix(location_projectionMatrix, projectionMatrix);
    }
private:
    const int location_transformationMatrix = GetUniformLocation("transform");
    const int location_lightDirection = GetUniformLocation("lightDirection");
    const int location_viewMatrix = GetUniformLocation("viewMatrix");
    const int location_projectionMatrix = GetUniformLocation("projectionMatrix");
};

#endif // SKYBOXSHADER_H_INCLUDED
