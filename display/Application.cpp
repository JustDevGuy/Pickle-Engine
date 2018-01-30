#include "Application.h"

Application::Application(std::string title, int width, int height, bool fullscreenMode)
{
    // Initialize GLFW
    if(!glfwInit())
        std::cout << "error in initialize GLFW" << std::endl;

    // Set some OpenGL basic configurations
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Check if the game is in fullscreen mode
    if(fullscreenMode)
    {
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        display = glfwCreateWindow(vidMode->width, vidMode->height, title.c_str(), nullptr, nullptr);
    }
    else
    {
        display = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowPos(display, 400, 100);
    }

    // Set infinity motion for mouse
    glfwSetInputMode(display, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enable OpenGL comparability
    glfwMakeContextCurrent(display);
    if(glewInit() != GLEW_OK)
        std::cout << "error in initialize GLEW" << std::endl;
    glViewport(0, 0, width, height);
}

void Application::Update()
{
    CalculateTime(); // Show frame rate in console

    // Clean up screen and setup
    glfwSwapBuffers(display);
    glfwPollEvents();

    // Calculate the mouse velocity
    oldMousePosX = mousePosX;
    mousePosX = GetMousePosX();
    mouseVelocityX = mousePosX - oldMousePosX;

    oldMousePosY = mousePosY;
    mousePosY = GetMousePosY();
    mouseVelocityY = mousePosY - oldMousePosY;

    if(glfwGetKey(display, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Exit key
        glfwSetWindowShouldClose(display, true);
}

// Getters
GLFWwindow* Application::GetWindow()
{
    return display;
}

double Application::GetMousePosX()
{
    glfwGetCursorPos(display, &mousePosX, nullptr);
    return mousePosX;
}

double Application::GetMousePosY()
{
    glfwGetCursorPos(display, nullptr, &mousePosY);
    return mousePosY;
}

float Application::GetMouseVelocityX()
{
    return mouseVelocityX;
}

float Application::GetMouseVelocityY()
{
    return mouseVelocityY;
}

int Application::GetWidth()
{
    int width;
    glfwGetWindowSize(display, &width, nullptr);
    return width;
}

int Application::GetHeight()
{
    int height;
    glfwGetWindowSize(display, nullptr, &height);
    return height;
}

bool Application::IsKeyPressed(int key)
{
    if(glfwGetKey(display, key) == GLFW_PRESS)
        return true;
    else
        return false;
}

bool Application::IsOpen()
{
    return !glfwWindowShouldClose(display);
}

double Application::GetDeltaTime()
{
    return this->deltaTime;
}

void Application::CalculateTime()
{
    lastTime = currentTime;
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;

    frameCount++;
    if(currentTime - lastClock >= 1.0)
    {
        std::cout << "FPS: " << (double)frameCount << std::endl;
        frameCount = 0;
        lastClock += 1.0f;
    }
}

void Application::Close()
{
    glfwDestroyWindow(display);
    glfwTerminate();
}
