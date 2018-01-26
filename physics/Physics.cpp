#include "Physics.h"

void Physics::UsePhysics(Entity& entity, float gravityForce, float deltaTime)
{
    // Check collision with the plane, if true, bounce
    if(entity.transform.GetPosition().y - entity.rigidbody.radius/2 <= 0)
    {
        entity.rigidbody.force.y = (-entity.rigidbody.force.y + entity.rigidbody.bauncing)/2;

        entity.rigidbody.force.x = Lerp(entity.rigidbody.force.x, 0.0f, 2.0f * deltaTime);
        entity.rigidbody.force.z = Lerp(entity.rigidbody.force.z, 0.0f, 2.0f * deltaTime);
    }
    else
    {
        // if false, apply more gravity to object
        entity.rigidbody.force.y += gravityForce * deltaTime;
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
        if(collider1.rigidbody.collisionType == 0 && collider1.rigidbody.collisionType == 0) // SPHERE && SPHERE
        {
            const float distance = glm::distance(collider1.transform.GetPosition(), collider2.transform.GetPosition());
            if(distance <= collider1.rigidbody.radius)
            {
                // Apply force between objects
                const glm::vec3 force = collider1.transform.GetPosition() - collider2.transform.GetPosition();
                collider1.rigidbody.force += 0.5f * force;
                collider2.rigidbody.force -= 0.5f * force;
            }
        }
        else if(collider1.rigidbody.collisionType == 1 && collider2.rigidbody.collisionType == 0) // BOX && SPHERE
        {
            const glm::vec3 pos = collider1.transform.GetPosition();
            const float distance = glm::distance(collider1.transform.GetPosition(), collider2.transform.GetPosition());
            const float radius = collider1.rigidbody.radius;
            const std::vector<glm::vec3> edges = {
                glm::vec3(pos.x - radius, pos.y - radius, pos.z - radius),
                glm::vec3(pos.x - radius, pos.y - radius, pos.z + radius),
                glm::vec3(pos.x - radius, pos.y + radius, pos.z - radius),
                glm::vec3(pos.x - radius, pos.y + radius, pos.z + radius),
                glm::vec3(pos.x + radius, pos.y - radius, pos.z - radius),
                glm::vec3(pos.x + radius, pos.y - radius, pos.z + radius),
                glm::vec3(pos.x + radius, pos.y + radius, pos.z - radius),
                glm::vec3(pos.x + radius, pos.y + radius, pos.z + radius) };

            for(int i = 0; i < 8; i++)
            {
                const float edgeDistance = glm::distance(edges[i], collider1.transform.GetPosition());
                if(distance < edgeDistance)
                {
                    const glm::vec3 force = edges[i] - collider2.transform.GetPosition();
                    collider1.rigidbody.force += 0.5f * force;
                    collider2.rigidbody.force -= 0.5f * force;
                }
            }
        }
        else if(collider1.rigidbody.collisionType == 1 && collider2.rigidbody.collisionType == 1) // BOX && BOX
        {
            const glm::vec3 pos = collider1.transform.GetPosition(), targetPos = collider2.transform.GetPosition();
            const float radius = collider1.rigidbody.radius, targetRadius = collider2.rigidbody.radius;

            const std::vector<glm::vec3> edges = {
                glm::vec3(pos.x - radius, pos.y - radius, pos.z - radius),
                glm::vec3(pos.x - radius, pos.y - radius, pos.z + radius),
                glm::vec3(pos.x - radius, pos.y + radius, pos.z - radius),
                glm::vec3(pos.x - radius, pos.y + radius, pos.z + radius),
                glm::vec3(pos.x + radius, pos.y - radius, pos.z - radius),
                glm::vec3(pos.x + radius, pos.y - radius, pos.z + radius),
                glm::vec3(pos.x + radius, pos.y + radius, pos.z - radius),
                glm::vec3(pos.x + radius, pos.y + radius, pos.z + radius) };

            const std::vector<glm::vec3> targetEdges = {
                glm::vec3(targetPos.x - targetRadius, targetPos.y - targetRadius, targetPos.z - targetRadius),
                glm::vec3(targetPos.x - targetRadius, targetPos.y - targetRadius, targetPos.z + targetRadius),
                glm::vec3(targetPos.x - targetRadius, targetPos.y + targetRadius, targetPos.z - targetRadius),
                glm::vec3(targetPos.x - targetRadius, targetPos.y + targetRadius, targetPos.z + targetRadius),
                glm::vec3(targetPos.x + targetRadius, targetPos.y - targetRadius, targetPos.z - targetRadius),
                glm::vec3(targetPos.x + targetRadius, targetPos.y - targetRadius, targetPos.z + targetRadius),
                glm::vec3(targetPos.x + targetRadius, targetPos.y + targetRadius, targetPos.z - targetRadius),
                glm::vec3(targetPos.x + targetRadius, targetPos.y + targetRadius, targetPos.z + targetRadius) };

            for(int i = 0; i < 8; i++) for(int e = 0; e < 8; e++)
            {
                const float edgeDistance = glm::distance(edges[i], collider1.transform.GetPosition());
                const float targetEdgeDistance = glm::distance(targetEdges[e], collider1.transform.GetPosition());
                if(targetEdgeDistance < edgeDistance)
                {
                    const glm::vec3 force = edges[i] - collider2.transform.GetPosition();
                    collider1.rigidbody.force += 0.5f * force;
                    collider2.rigidbody.force -= 0.5f * force;
                }
            }
        }
    }
}

float Physics::Lerp(float a, float b, float t)
{
    return (1-t)*a + t*b;
}


