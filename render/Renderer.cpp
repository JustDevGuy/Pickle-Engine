#include "Renderer.h"

void Renderer::Render(glm::vec3 lightDirection, Camera camera)
{
    Prepare(0.f, 0.f, 0.f);

    shader.Start();
    shader.LoadLight(lightDirection);
    shader.LoadViewMatrix(camera.GetProjection() * camera.GetViewMatrix());

    for(auto const& i : entities)
    {
        PrepareModel(i.first);
        std::vector<Entity> batch = i.second;
        for(auto entity : batch)
        {
            PrepareInstance(entity);
            glDrawElements(GL_TRIANGLES, entity.model.GetVertexCount(), GL_UNSIGNED_INT, 0);
        }
        UnbindModel();
    }

    shader.Stop();
    entities.clear();
}

void Renderer::AddEntity(Entity entity)
{
    if(entities.find(entity.model) != entities.end()) ///MODEL FOUND
    {
        entities[entity.model].push_back(entity);
    }
    else ///MODEL NOT FOUND
    {
        std::vector<Entity> newBatch = {entity};
        entities[entity.model] = newBatch;
    }
}

void Renderer::AddEntities(std::vector<Entity>identityList)
{
    if(entities.find(identityList[0].model) != entities.end()) ///MODEL FOUND
    {
        entities[identityList[0].model].insert(entities[identityList[0].model].end(), identityList.begin(), identityList.end());
    }
    else ///MODEL NOT FOUND
    {
        entities[identityList[0].model] = identityList;
    }
}

void Renderer::CleanUp()
{
    shader.CleanUp();
}

void Renderer::Prepare(float r, float g, float b) //Prepare the screen
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 1.0f);
}

void Renderer::PrepareModel(Model model) //Prepare model for rendering
{
    if(model.GetFakeLighting()) //Model doens't receive light if enable
        shader.UseFakeLighting(true);

    if(model.GetIsTransparency()) //Transparent texture
        glDisable(GL_CULL_FACE);

    if(model.GetUseReflection())
        shader.UseReflection(true);

    glBindVertexArray(model.GetVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
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

void Renderer::PrepareInstance(Entity identity) //Prepare model texture and shader
{
    shader.LoadTransformationMatrix(identity.transform.GetTransform());
    identity.texture.Bind();
}
