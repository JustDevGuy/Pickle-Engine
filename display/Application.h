#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <glfw3.h>
#include <string>
#include <iostream>

class Application
{
public:
    Application(std::string title, int width, int height, bool fullscreenMode);

    GLFWwindow* GetWindow();
    double GetDeltaTime();
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool IsKeyPressed(int key);

    double GetMousePosX();
    double GetMousePosY();
    float GetMouseVelocityX();
    float GetMouseVelocityY();

    void Update();
    void Close();
private:
    void CalculateTime();

    double oldMousePosX, oldMousePosY;
    double mousePosX, mousePosY;
    float mouseVelocityX, mouseVelocityY;

    double currentTime = glfwGetTime();
    double lastTime = 0, lastClock = 0;
    double deltaTime;
    int frameCount;
    GLFWwindow* display;
};

#endif // APPLICATION_H
