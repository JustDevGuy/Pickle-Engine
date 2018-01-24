#version 330 core

in vec2 tex_coords;
in vec3 pass_normal;
in vec3 toLightVector;
out vec4 fragColor;

uniform sampler2D modelTexture;

void main() {
	vec3 unitNormal = normalize(pass_normal);
	vec3 unitLightVector = normalize(toLightVector);
	
	float nDotl = dot(unitNormal,unitLightVector);
	float brightness = max(nDotl, 0.2);
	vec3 diffuse = brightness * vec3(1,1,1);
	
	fragColor = vec4(diffuse, 1.0) * texture(modelTexture, tex_coords);
}