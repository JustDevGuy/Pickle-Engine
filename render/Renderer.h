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
    void Render(glm::vec3 lightDirection, Camera camera); // Render all entities and clean the list

    void AddEntity(Entity entity); // Add a entity to list
    void AddEntities(std::vector<Entity> entityList); // Add multiple entities

    void CleanUp(); // Destroy the renderer
private:
    std::map<Model,std::vector<Entity>> entities; // List of entities
    StaticShader shader; // One static shader for all models

    static void Prepare(float r, float g, float b); // RGB of background color

    // Render model functions
    void PrepareModel(Model model);
    void PrepareInstance(Entity entity);
    void UnbindModel();
};


#endif // RENDERER_H
