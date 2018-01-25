#include "PickleEngine.h"

int main(int argc, char* argv[])
{
    //Initialize the basics
    Application window("Pickle Engine", 800, 600, false);
    Camera camera(glm::vec3(0, 5, 20), window.GetWidth(), window.GetHeight());
    Physics physics;
    Loader loader;

    //Create models
    Entity plane(loader.LoadModel(".//res//entities//plane.obj"), ".//res//textures//stoneFloor.png", glm::vec3(0,0,0), glm::vec3(0,0,0));

    Entity sphere(loader.LoadModel(".//res//entities//monkey.obj"), ".//res//textures//solidColor.png", glm::vec3(0,0,0), glm::vec3(0,0,0));
    std::vector<Entity> spheres;
    sphere.rigidbody.radius = 1.4f;
    sphere.model.SetUseReflection(true);

    for(int i = 1; i < 40; i++)
    {
        sphere.transform.SetPosition(rand() % 5 + (-5), rand() % 5 + 15, rand() % 5 + (-5));
        sphere.rigidbody.id = i;
        spheres.push_back(sphere);
    }

    //Create the render
    Renderer renderer;

    //Main game loop
    while(window.IsOpen())
    {
        //Transform movement example
        camera.Move(window);

        //Set one of the entities to camera, to calculate collisions to it
        spheres[0].transform.SetPosition(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        spheres[0].transform.SetRotation(0, 0, 0);
        spheres[0].transform.SetScale(0);

        //Basic physics
        if(!window.IsKeyPressed(GLFW_KEY_SPACE))
        {
            for(auto &rigidbody : spheres)
            {
                physics.UsePhysics(rigidbody, -7.5f, window.GetDeltaTime());
                for(auto &target : spheres)
                {
                    physics.CheckCollision(rigidbody, target, window.GetDeltaTime());
                }
            }
        }

        //Process the models to be rendered
        renderer.AddEntities(spheres);
        renderer.AddEntity(plane);

        //Render all
        renderer.Render(glm::vec3(0,10,0), camera);
        window.Update();
    }

    //Clean up and exit
    loader.CleanUp();
    renderer.CleanUp();
    window.Close();
    return 0;
}
