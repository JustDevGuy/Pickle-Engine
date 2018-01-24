#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glfw3.h>
#include <string>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
    void CreateTexture(const std::string& fileName);
    void CreateCubeMap(const std::string textureFiles[6]);
    void Bind();
    void BindAsCubeMap();
    void CleanUp();
private:
    GLuint textureID;
    unsigned char* imageData;
    int width, height, numComponents;
};

#endif // TEXTURE_H
