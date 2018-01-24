#include "Model.h"

Model::Model(GLuint vaoID, int vertexCount)
{
    this->vaoID = vaoID;
    this->vertexCount = vertexCount;
}

// Setters
void Model::SetIsTransparency(bool value)
{
    this->isTransparency = value;
}

void Model::SetFakeLighting(bool value)
{
    this->useFakeLighting = value;
}

void Model::SetUseReflection(bool value)
{
    this->useReflection = value;
}

// Getters
bool Model::GetIsTransparency()
{
    return this->isTransparency;
}

bool Model::GetFakeLighting()
{
    return this->useFakeLighting;
}

bool Model::GetUseReflection()
{
    return this->useReflection;
}

GLuint Model::GetVaoID()
{
    return this->vaoID;
}

int Model::GetVertexCount()
{
    return this->vertexCount;
}
