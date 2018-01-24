#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>
#include "Model.h"
#include "Renderer.h"
#include "Entity.h"
#include "Camera.h"
#include "../shaders/StaticShader.h"

class Renderer
{
public:
    void Render(glm::vec3 lightDirection, Camera camera);

    void AddEntity(Entity entity);
    void AddEntities(std::vector<Entity> identityList);

    void CleanUp();
private:
    std::map<Model,std::vector<Entity>> entities;
    StaticShader shader;

    void Prepare(float r, float g, float b);
    void PrepareModel(Model model);
    void PrepareInstance(Entity identity);
    void UnbindModel();
};


#endif // RENDERER_H
