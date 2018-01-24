#include "Entity.h"

Entity::Entity(Model m_model, const std::string& textureFile, glm::vec3 position, glm::vec3 rotation) : model(m_model)
{
    transform.Create(position, rotation, 1);
    texture.CreateTexture(textureFile);
}

void Entity::Destroy()
{
    texture.CleanUp();
}
