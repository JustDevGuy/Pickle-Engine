#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "Camera.h"
#include "Transform.h"
#include "Texture.h"
#include "obj_loader.h"
#include "../shaders/TerrainShader.h"

class Terrain
{
public:
    Terrain(glm::vec3 terrainPosition, int smooth, const std::string& heightmapFile, const std::string& textureFile);
    void RenderTerrain(Camera camera);
    void Destroy();
private:
    void CreateTerrain(std::string heightmapFile, int smooth);
    int GetPixelHeight(unsigned char* data, int x, int imageWidth, int y, int smooth);

    GLuint terrainVAO, verticesVBO, normalsVBO, indicesVBO, textureVBO;
    int verticesCount;

    Texture terrainTexture;
    Transform transform;
    TerrainShader shader;
};


#endif // TERRAIN_H
