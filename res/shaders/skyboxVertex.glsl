#version 330 core

layout(location = 0) in vec3 position;

out vec3 tex_coords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transform;

void main()
{
	vec4 pos = projectionMatrix * viewMatrix * transform * vec4(position, 1.0);
	gl_Position = pos.xyww;
	tex_coords = position;
}