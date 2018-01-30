#include "Renderer.h"

void Renderer::Prepare(float r, float g, float b) //Prepare the screen
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 1.0f);
}

void Renderer::Render(glm::vec3 lightDirection, Camera camera)
{
    Prepare(0.f, 0.f, 0.f);

    shader.Start();
    shader.LoadLight(lightDirection);
    shader.LoadViewMatrix(camera.GetProjection() * camera.GetViewMatrix());

    for(auto const &i : entities)
    {
        PrepareModel(i.first);
        Model model = i.first;
        const int modelCount = model.GetVertexCount();

        for(auto const &entity : i.second)
        {
            PrepareInstance(entity);
            glDrawElements(GL_TRIANGLES, modelCount, GL_UNSIGNED_INT, nullptr);
        }
        UnbindModel();
    }

    shader.Stop();
    entities.clear();
}

void Renderer::AddEntity(Entity entity)
{
    entities[entity.model].push_back(entity);
}

void Renderer::AddEntities(std::vector<Entity> entityList)
{
    entities[entityList[0].model].insert(entities[entityList[0].model].end(), entityList.begin(), entityList.end());
}

void Renderer::PrepareModel(Model model) //Prepare model for rendering
{
    if(model.GetFakeLighting()) //Model doesn't receive light if enable
        shader.UseFakeLighting(true);

    if(model.GetIsTransparency()) //Transparent texture
        glDisable(GL_CULL_FACE);

    if(model.GetUseReflection()) //Specular lighting
        shader.UseReflection(true);

    glBindVertexArray(model.GetVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Renderer::PrepareInstance(Entity entity) //Prepare model texture and shader
{
    shader.LoadTransformationMatrix(entity.transform.GetTransform());
    entity.texture.Bind();
}

void Renderer::UnbindModel()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    shader.UseFakeLighting(false);
    shader.UseReflection(false);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Renderer::CleanUp()
{
    shader.CleanUp();
}
