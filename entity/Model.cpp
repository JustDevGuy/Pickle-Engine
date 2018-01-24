#include "Model.h"

Model::Model(GLuint vaoID, int vertexCount)
{
    this->vaoID = vaoID;
    this->vertexCount = vertexCount;
}

void Model::SetIsTransparency(bool value)
{
    this->isTransparency = value;
}

bool Model::GetIsTransparency()
{
    return this->isTransparency;
}

void Model::SetFakeLighting(bool value)
{
    this->useFakeLighting = value;
}

bool Model::GetFakeLighting()
{
    return this->useFakeLighting;
}

void Model::SetUseReflection(bool value)
{
    this->useReflection = value;
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
