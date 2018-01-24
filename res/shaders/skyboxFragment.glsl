#version 330 core

in vec3 tex_coords;

uniform samplerCube skybox;

out vec4 fragColor;

void main()
{
	fragColor = texture(skybox, tex_coords);
}