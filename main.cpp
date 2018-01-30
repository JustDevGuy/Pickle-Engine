#include "PickleEngine.h"

int main(int argc, char* argv[])
{
    //Initialize the basics
    Application window("Pickle Engine", 800, 600, false);
    Camera camera(glm::vec3(0, 5, 20), window.GetWidth(), window.GetHeight());
    Physics physics;
    Loader loader;

    //Create models
    Entity plane(loader.LoadModel(".//res//models//plane.obj"), ".//res//textures//stoneFloor.png", glm::vec3(0,0,0), glm::vec3(0,0,0));

    Entity cube(loader.LoadModel(".//res//models//cube.obj"), ".//res//textures//stoneFloor.png", glm::vec3(0,1.5f,0), glm::vec3(0,0,0));
    cube.rigidbody.collisionType = 1;
    cube.rigidbody.radius = 2.0f;

    Entity sphere(loader.LoadModel(".//res//models//monkey.obj"), ".//res//textures//solidColor.png", glm::vec3(0,0,0), glm::vec3(0,0,0));
    sphere.rigidbody.radius = 1.4f;
    sphere.rigidbody.collisionType = 0;
    sphere.model.SetUseReflection(true);

    std::vector<Entity> spheres;
    for(int i = 1; i < 100; i++)
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
        if(window.IsKeyPressed(GLFW_KEY_SPACE))
        {
            for(auto &rigidbody : spheres)
            {
                physics.UsePhysics(rigidbody, -7.5f, window.GetDeltaTime());
                physics.CheckCollision(cube, rigidbody, window.GetDeltaTime());
                for(auto &target : spheres)
                {
                    physics.CheckCollision(rigidbody, target, window.GetDeltaTime());
                }
            }
        }

        //Process the models to be rendered
        renderer.AddEntity(cube);
        renderer.AddEntity(plane);
        renderer.AddEntities(spheres);

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
