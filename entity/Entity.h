#ifndef ENTITY_H
#define ENTITY_H

#include "Loader.h"
#include "Model.h"
#include "Transform.h"
#include "Loader.h"
#include "Texture.h"

struct RigidBody
{
    int id;
    bool isStatic;
    glm::vec3 force;
    float radius;
    float bauncing;
};

class Entity
{
public:
    Entity(Model m_model, const std::string& textureFile, glm::vec3 position, glm::vec3 rotation);
    void Destroy();

    Model model;
    Texture texture;
    Transform transform;
    RigidBody rigidbody;
};

#endif // ENTITY_H
