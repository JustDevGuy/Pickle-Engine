#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normals;

out vec2 tex_coords;
out vec3 pass_normal;
out vec3 toLightVector;

uniform mat4 transform;
uniform mat4 view;
uniform vec3 lightDirection;

void main() {
	vec4 worldPosition = transform * vec4(position, 1.0);
	
	gl_Position = view * worldPosition;
	tex_coords = texCoord/3;
	pass_normal = (transform * vec4(normals,0.0)).xyz;
	
	toLightVector = lightDirection - worldPosition.xyz;
}