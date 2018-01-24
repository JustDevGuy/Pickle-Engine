#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include "Transform.h"

class Model
{
public:
    Model(GLuint vaoID, int vertexCount);

    // Model transparency manager
    void SetIsTransparency(bool value);
    bool GetIsTransparency();

    // Model reflections manager
    void SetUseReflection(bool value);
    bool GetUseReflection();

    // Model fake lights manager
    void SetFakeLighting(bool value);
    bool GetFakeLighting();

    // OpenGL
    GLuint GetVaoID();
    int GetVertexCount();

    bool operator<(const Model& rhs) const
    {
        return (vaoID < rhs.vaoID);
    }
private:
    // Components of effects
    bool isTransparency = false;
    bool useFakeLighting = false;
    bool useReflection = false;

    // OpenGL
    GLuint vaoID;
    int vertexCount;
};

#endif // MODEL_H
