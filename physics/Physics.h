#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <iostream>
#include "Entity.h"

class Physics
{
public:
    Physics(float gravity);
    void UsePhysics(Entity& entity, float deltaTime); // Use physics for the rigidbody
    void CheckCollision(Entity& collider1, Entity& collider2, float deltaTime); // Calculate collision between two rigidbodies
private:
    float gravity; // Gravity force
};

#endif // PHYSICS_H
