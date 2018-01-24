#ifndef TERRAINSHADER_H_INCLUDED
#define TERRAINSHADER_H_INCLUDED

#include "ShaderSource.h"

class TerrainShader : public ShaderSource
{
public:
    TerrainShader() : ShaderSource(".//res//shaders//terrainVertex.glsl", ".//res//shaders//terrainFragment.glsl")
    {
    }

    void LoadLight(glm::vec3 lightDirection) //Lighting ray direction
    {
        LoadVector(location_lightDirection, lightDirection);
    }

    void LoadTransformationMatrix(glm::mat4 matrix) //Translate, rotate and scale of model
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
    const int location_lightDirection = GetUniformLocation("lightDirection");
};

#endif // TERRAINSHADER_H_INCLUDED
