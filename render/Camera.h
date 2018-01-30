#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Application.h"

class Camera
{
public:
    // Constructor
    Camera(glm::vec3 startPosition, int width, int height)
    {
        m_position -= startPosition;
        float aspectRatio = (float) width / (float) height;
        m_projection = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
    }

    glm::mat4 GetProjection()
    {
        return m_projection;
    }

    // Update camera information
    glm::mat4 GetViewMatrix()
    {
        UpdateViewMatrix();
        return m_view;
    }

    // Getters and setters of camera
    glm::vec3 GetPosition() { return -this->m_position; }
    void SetPosition(glm::vec3 pos) { m_position.x = pos.x; m_position.y = pos.y; m_position.z = pos.z; }

    // Move camera function
    void Move(Application window)
    {
        // Camera movement with keys
        if(window.IsKeyPressed(GLFW_KEY_W)) dz = -9 * window.GetDeltaTime();
        else if(window.IsKeyPressed(GLFW_KEY_S)) dz = 9 * window.GetDeltaTime();
        else dz = 0;

        if(window.IsKeyPressed(GLFW_KEY_A)) dx = 9 * window.GetDeltaTime();
        else if(window.IsKeyPressed(GLFW_KEY_D)) dx = -9 * window.GetDeltaTime();
        else dx = 0;

        // Camera movement with mouse
        m_rotation.y += window.GetMouseVelocityX() * 0.4f * window.GetDeltaTime();
        m_rotation.x += window.GetMouseVelocityY() * 0.4f * window.GetDeltaTime();
        m_rotation.x = glm::clamp(m_rotation.x, -1.0f, 1.3f); // Limit camera X rotation
        m_rotation.y = glm::clamp(m_rotation.y, -2.0f, 2.0f);

        // Set the view matrix with the camera positions and rotations
        glm::vec3 forward(m_view[0][2], m_view[1][2], m_view[2][2]);
        glm::vec3 strafe(m_view[0][0], m_view[1][0], m_view[2][0]);
        m_position += (-dz * forward + dx * strafe);

        // Update view matrix
        UpdateViewMatrix();
    }

private:
    glm::vec3 m_position;
    glm::quat m_rotation = glm::vec3(0,0,0);
    glm::mat4 m_projection;
    glm::mat4 m_view;
    float dx, dz;

    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    const float FOV = 70;
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 1000;

    void UpdateViewMatrix()
    {
        glm::quat pitch = glm::angleAxis(m_rotation.x, glm::vec3(1,0,0));
        glm::quat yaw = glm::angleAxis(m_rotation.y, glm::vec3(0,1,0));

        glm::mat4 viewRotation = glm::mat4_cast((glm::quat)glm::normalize(pitch * yaw));
        glm::mat4 translate = glm::mat4(1.0f);
        translate = glm::translate(translate, m_position);

        m_view = viewRotation * translate;
    }
};

#endif // CAMERA_H_INCLUDED
