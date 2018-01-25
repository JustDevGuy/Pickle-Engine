#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <iostream>
#include "Entity.h"

class Physics
{
public:
    static void UsePhysics(Entity& entity, float gravityForce, float deltaTime); // Use physics for the rigidbody
    static void CheckCollision(Entity& collider1, Entity& collider2, float deltaTime); // Calculate collision between two rigidbodies
};

#endif // PHYSICS_H
