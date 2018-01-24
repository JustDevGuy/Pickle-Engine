#include "Skybox.h"

Skybox::Skybox(std::string textureFiles[6])
{
    skyboxTexture.CreateCubeMap(textureFiles);
    skyboxTransform.Create(glm::vec3(0,0,0), glm::vec3(0,0,0), 1);

    glGenVertexArrays(1,&skyboxVAO);
    glBindVertexArray(skyboxVAO);

    glGenBuffers(1,&skyboxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    verticesCount = 36;
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Skybox::RenderSkybox(Camera camera)
{
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    skyboxShader.Start();
    glBindVertexArray(skyboxVAO);
    glEnableVertexAttribArray(0);

    skyboxShader.LoadViewMatrix(camera.GetViewMatrix(), camera.GetProjection());
    skyboxShader.LoadTransformationMatrix(skyboxTransform.GetTransform());
    skyboxTexture.BindAsCubeMap();
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    skyboxShader.Stop();
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void Skybox::Destroy()
{
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);

    skyboxShader.CleanUp();
    skyboxTexture.CleanUp();
}
