#include "Terrain.h"

Terrain::Terrain(glm::vec3 terrainPosition, int smooth, const std::string& heightmapFile, const std::string& textureFile)
{
    transform.Create(glm::vec3(terrainPosition.x, terrainPosition.y, terrainPosition.z), glm::vec3(0,0,0), 1);

    terrainTexture.CreateTexture(textureFile);
    CreateTerrain(heightmapFile, smooth);

    //Load once the transformation and the light
    shader.Start();
    shader.LoadTransformationMatrix(transform.GetTransform());
    shader.LoadLight(glm::vec3(0,300,40));
    shader.Stop();
}

//The basic terrain generation
void Terrain::RenderTerrain(Camera camera)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.Start();
    glBindVertexArray(terrainVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    shader.LoadViewMatrix(camera.GetProjection() * camera.GetViewMatrix());
    terrainTexture.Bind();
    glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
    shader.Stop();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//Calculate the height of the vertex in the terrain
int Terrain::GetPixelHeight(unsigned char* data, int imageWidth, int x, int y, int smooth)
{
    unsigned char* pixelOffset = data + (x + imageWidth * y); //Get the image
    float pixelHeight = (float)pixelOffset[1]; //Get height of the pixel
    return (pixelHeight/imageWidth) * smooth; //Return the height with smooth
}

void Terrain::CreateTerrain(std::string heightmapFile, int smooth)
{
    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> textureCoords;
    std::vector<unsigned int> indices;

    int x, y, comps;
    unsigned char *data = stbi_load(heightmapFile.c_str(), &x, &y, &comps, 1);

    int terrainWidth = x;
    int terrainLength = y;

    int i = 0;
    for(int z = 0; z < terrainLength; z++) for(int x = 0; x < terrainWidth; x++)
    {
        //Calculate vertices
        glm::vec3 vertex = glm::vec3(x-terrainWidth/2, GetPixelHeight(data, y, x, z, smooth), z-terrainLength/2);

        //Put the vertices and texture coords
        vertices.push_back(vertex);
        textureCoords.push_back(glm::vec2(x,z));

        //Calculate the normals based in the terrain height
        float heightL = GetPixelHeight(data, y, x-1, z, smooth);
        float heightR = GetPixelHeight(data, y, x+1, z, smooth);
        float heightD = GetPixelHeight(data, y, x, z-1, smooth);
        float heightU = GetPixelHeight(data, y, x, z+1, smooth);
        normals.push_back(glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU)));

        //Calculate indices
        if((i+1 % (int)terrainWidth) != 0 && z+1 < terrainLength)
        {
            glm::vec3 triangle1, triangle2;
            if(i % 2 == 0)
            {
                triangle1 = glm::vec3(i, i+terrainWidth, i+terrainWidth+1);
                triangle2 = glm::vec3(i, i+terrainWidth+1, i+1);
            }
            else
            {
                triangle1 = glm::vec3(i, i+terrainWidth, i+1);
                triangle2 = glm::vec3(i+1, i+terrainWidth, i+terrainWidth+1);
            }

            if(x < terrainWidth-1)
            {
                indices.push_back(triangle1.x); indices.push_back(triangle1.y); indices.push_back(triangle1.z);
                indices.push_back(triangle2.x); indices.push_back(triangle2.y); indices.push_back(triangle2.z);
            }
        }

        i++;
    }

    //Bind openGL attributes
    verticesCount = indices.size();

    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(textureCoords[0]), textureCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

    glGenBuffers(1, &normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

    glGenBuffers(1, &indicesVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Terrain::Destroy()
{
    shader.CleanUp();
}
