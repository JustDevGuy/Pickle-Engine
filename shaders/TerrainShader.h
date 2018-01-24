#ifndef TERRAINSHADER_H_INCLUDED
#define TERRAINSHADER_H_INCLUDED

#include "ShaderSource.h"

class TerrainShader : public ShaderSource
{
public:
    // Load shaders
    TerrainShader() : ShaderSource(".//res//shaders//terrainVertex.glsl", ".//res//shaders//terrainFragment.glsl")
    {
    }

    // Load light position
    void LoadLight(glm::vec3 lightDirection)
    {
        LoadVector(location_lightDirection, lightDirection);
    }

    // Load terrain transform
    void LoadTransformationMatrix(glm::mat4 matrix)
    {
        LoadMatrix(location_transformationMatrix, matrix);
    }

    // Load camera matrix to calculate terrain in screen
    void LoadViewMatrix(glm::mat4 viewMatrix)
    {
        LoadMatrix(location_viewMatrix, viewMatrix);
    }
private:
    // Uniform variables locations
    const int location_transformationMatrix = GetUniformLocation("transform");
    const int location_viewMatrix = GetUniformLocation("view");
    const int location_lightDirection = GetUniformLocation("lightDirection");
};

#endif // TERRAINSHADER_H_INCLUDED
