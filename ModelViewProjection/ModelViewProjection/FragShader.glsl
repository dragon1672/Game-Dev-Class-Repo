#version 400

in vec4 outColor;
out vec4 finalColor;


uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;
uniform bool diffuseInFrag;

uniform bool passThrough;

uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 diffusePos;

void main() {
	finalColor = outColor;
}