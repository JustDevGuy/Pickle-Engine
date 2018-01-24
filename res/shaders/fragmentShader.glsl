#version 400 core

in vec2 tex_coords;
in vec3 pass_normal;
in vec3 toLightVector;
in vec3 toCameraVector;
out vec4 fragColor;

uniform sampler2D modelTexture;
uniform float useFakeLighting;
uniform float useReflection;

float shineDamper = 10;
float reflectivity = 1;

void main() {
	vec3 actualNormal = pass_normal;
	if(useFakeLighting > 0.5)
		actualNormal = vec3(0.0,1.0,0.0);
		
	if(useReflection > 0.5) {
		shineDamper = 10;
		reflectivity = 1;
	} else {
		shineDamper = 0;
		reflectivity = 0;
	}
		
	vec3 unitNormal = normalize(actualNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl,0.2);
	vec3 diffuse = brightness * vec3(1,1,1);
	
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection,unitNormal);
	float specularFactor = dot(reflectedLightDirection,unitVectorToCamera);
	specularFactor = max(specularFactor,0.0);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * vec3(1,1,1);

	fragColor = vec4(diffuse,1.0) * texture(modelTexture, tex_coords) + vec4(finalSpecular,1.0);
}