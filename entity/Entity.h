#ifndef ENTITY_H
#define ENTITY_H

#include "Loader.h"
#include "Model.h"
#include "Transform.h"
#include "Loader.h"
#include "Texture.h"

// Physics calculations
struct RigidBody
{
    unsigned int id;
    float radius = 1;
    float bauncing;
    unsigned int collisionType;
    bool isStatic;
    glm::vec3 force;
};

class Entity
{
public:
    // Constructor and destructor
    Entity(Model m_model, const std::string& textureFile, glm::vec3 position, glm::vec3 rotation);
    void Destroy();

    // Components
    Model model;
    Texture texture;
    Transform transform;
    RigidBody rigidbody;
};

#endif // ENTITY_H
