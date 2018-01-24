#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normals;

out vec2 tex_coords;
out vec3 pass_normal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transform;
uniform mat4 view;
uniform vec3 lightPosition;

void main() {
	vec4 worldPosition = transform * vec4(position, 1.0); 
	gl_Position = view * worldPosition;
	tex_coords = texCoord;
	
	pass_normal = (transform * vec4(normals,0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
}