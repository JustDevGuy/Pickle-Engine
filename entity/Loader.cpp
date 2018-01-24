#include "Loader.h"

Model Loader::LoadModel(std::string objFile)
{
    IndexedModel model = OBJModel(objFile).ToIndexedModel();

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);

    glBindVertexArray(vaoID);
    BindIndicesVBO(model.indices);
    StoreDataInAttributeList(0, 3, model.positions);
    StoreDataInAttributeList(1, 2, model.texCoords);
    StoreDataInAttributeList(2, 3, model.normals);
    glBindVertexArray(0);

    int vertexCount = model.indices.size();
    Model out_model(vaoID, vertexCount);
    return out_model;
}

void Loader::StoreDataInAttributeList(int location, int attributeSize, std::vector<glm::vec3>data)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(location, attributeSize, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreDataInAttributeList(int location, int attributeSize, std::vector<glm::vec2>data)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(location, attributeSize, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::BindIndicesVBO(std::vector<unsigned int> indices)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}

void Loader::CleanUp()
{
    for(GLuint i = 0; i < vaos.size() * sizeof(vaos[0]); i++)
        glDeleteVertexArrays(1, &vaos[i]);
    for(GLuint i = 0; i < vbos.size() * sizeof(vbos[0]); i++)
        glDeleteBuffers(1, &vbos[i]);
}
