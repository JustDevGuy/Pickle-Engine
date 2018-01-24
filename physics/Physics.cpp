#include "Physics.h"

Physics::Physics(float gravity)
{
    this->gravity = gravity;
}

void Physics::UsePhysics(Entity& entity, float deltaTime)
{
    // Check collision with the plane, if true, bounce
    if(entity.transform.GetPosition().y - entity.rigidbody.radius/2 <= 0)
    {
        entity.rigidbody.force.y = (-entity.rigidbody.force.y + entity.rigidbody.bauncing)/2;

        if(entity.rigidbody.force.x >= 0 || entity.rigidbody.force.x <= 0)
            entity.rigidbody.force.x -= (entity.rigidbody.force.x/2) * deltaTime;
        if(entity.rigidbody.force.z >= 0 || entity.rigidbody.force.z <= 0)
            entity.rigidbody.force.z -= (entity.rigidbody.force.z/2) * deltaTime;
    }
    else
    {
        // if false, apply more gravity to object
        entity.rigidbody.force.y += gravity * deltaTime;
    }

    // Apply forces on the transform positions
    if(!entity.rigidbody.isStatic)
    {
        entity.transform.Translate(entity.rigidbody.force.x * deltaTime,
            entity.rigidbody.force.y * deltaTime, entity.rigidbody.force.z * deltaTime);

        entity.transform.Rotate((-entity.rigidbody.force.x/5) * deltaTime,
            (-entity.rigidbody.force.y/5) * deltaTime, (-entity.rigidbody.force.z/5) * deltaTime);
    }
}

void Physics::CheckCollision(Entity& collider1, Entity& collider2, float deltaTime)
{
    // Check if not colliding with the same object
    if(collider1.rigidbody.id != collider2.rigidbody.id)
    {
        float distance = glm::distance(collider1.transform.GetPosition(), collider2.transform.GetPosition());
        if(distance <= collider1.rigidbody.radius)
        {
            // Apply force between objects
            glm::vec3 force = collider1.transform.GetPosition() - collider2.transform.GetPosition();
            collider1.rigidbody.force += (force + collider1.rigidbody.bauncing) * deltaTime;
            collider2.rigidbody.force -= (force + collider2.rigidbody.bauncing) * deltaTime;
        }
    }
}


