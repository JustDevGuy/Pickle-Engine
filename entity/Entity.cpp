#include "Entity.h"

Entity::Entity(Model m_model, const std::string& textureFile, glm::vec3 position, glm::vec3 rotation) : model(m_model)
{
    // Create components of the entity
    transform.Create(position, rotation, 1);
    texture.CreateTexture(textureFile);
}

// Clean Up entity components
void Entity::Destroy()
{
    texture.CleanUp();
}
