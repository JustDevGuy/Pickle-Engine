#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include "Transform.h"

class Model
{
public:
    Model(GLuint vaoID, int vertexCount);
    void SetIsTransparency(bool value);
    bool GetIsTransparency();

    void SetUseReflection(bool value);
    bool GetUseReflection();

    void SetFakeLighting(bool value);
    bool GetFakeLighting();

    GLuint GetVaoID();
    int GetVertexCount();

    bool operator<(const Model& rhs) const
    {
        return (vaoID < rhs.vaoID);
    }
private:
    bool isTransparency = false;
    bool useFakeLighting = false;
    bool useReflection = false;
    GLuint vaoID;
    int vertexCount;
};

#endif // MODEL_H
