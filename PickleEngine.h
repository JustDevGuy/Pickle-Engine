#ifndef PICKLEENGINE_H_INCLUDED
#define PICKLEENGINE_H_INCLUDED

/*
Include all classes to use in one include
Application: Create window and input
Loader: load models to game
Renderer: render entities in the window
Entity: all components in one class to use
Camera: move in the world space
Terrain: environment creation with heightmaps or perlin noise
Skybox: create a sky for game
Physics: gravity, rigidbodies and other physics components
*/

#include "Application.h"
#include "Loader.h"
#include "Renderer.h"
#include "Entity.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Physics.h"

#endif // PICKLEENGINE_H_INCLUDED
