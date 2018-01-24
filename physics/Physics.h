#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <iostream>
#include "Entity.h"

class Physics
{
public:
    Physics(float gravity);
    void UsePhysics(Entity& entity, float deltaTime);
    void CheckCollision(Entity& collider1, Entity& collider2, float deltaTime);
private:
    float gravity;
};

#endif // PHYSICS_H
