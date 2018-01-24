#ifndef LOADER_H
#define LOADER_H

#include <GL/glew.h>
#include <vector>
#include <cstring>
#include <iostream>
#include "Model.h"
#include "obj_loader.h"

class Loader
{
public:
    Model LoadModel(std::string objFile);
    void CleanUp();
private:
    void StoreDataInAttributeList(int location, int attributeSize, std::vector<glm::vec3> data);
    void StoreDataInAttributeList(int location, int attributeSize, std::vector<glm::vec2> data);
    void BindIndicesVBO(std::vector<unsigned int> indices);

    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
};

#endif // LOADER_H
