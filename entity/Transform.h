#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
    void Create(glm::vec3 m_position, glm::vec3 m_rotation, float m_scale)
    {
        position = m_position;
        rotation = m_rotation;
        scale = m_scale;
    }

    glm::mat4 GetTransform()
    {
        glm::mat4 positionMatrix = glm::translate(position);
        glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale, scale, scale));
        glm::mat4 xRotationMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 yRotationMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 zRotationMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
        glm::mat4 rotationMatrix = xRotationMatrix * yRotationMatrix * zRotationMatrix;

        return positionMatrix * rotationMatrix * scaleMatrix;
    }

    void SetPosition(float x, float y, float z)
    {
        position = glm::vec3(x,y,z);
    }
    void SetRotation(float x, float y, float z)
    {
        rotation = glm::vec3(x,y,z);
    }
    void SetScale(float newScale)
    {
        scale = newScale;
    }
    void Translate(float x, float y, float z)
    {
        position.x += x;
        position.y += y;
        position.z += z;
    }
    void Rotate(float x, float y, float z)
    {
        rotation.x += x;
        rotation.y += y;
        rotation.z += z;
    }
    void IncreaseScale(float newScale)
    {
        scale += newScale;
    }
    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetRotation() { return rotation; }
    float GetScale() { return scale; }
private:
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
};

#endif // TRANSFORM_H_INCLUDED
