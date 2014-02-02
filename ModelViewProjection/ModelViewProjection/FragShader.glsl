#version 400

in vec4 outColor;
in vec3 outPos;
in vec3 outNorm;
out vec4 finalColorForOutput;


uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;
uniform bool diffuseInFrag;

uniform bool passThrough;

uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 diffusePos;

uniform bool enableOverrideColor;
uniform vec3 overrideColor;

vec3 diffuseLightAmount() {
	vec3 diff = diffusePos - vec3(outPos);
	diff = normalize(diff);
	vec3 rotatedNorm = normalize(mat3(model2WorldTransform) * normalize(outNorm));
	return dot(rotatedNorm,diff) * diffuseLight;
}

vec3 combineLight(vec3 diffuse, vec3 amb) {
	return diffuse + amb;
}

void main() {
	vec3 finalCol = vec3(outColor);
	if(diffuseInFrag && !passThrough) {
		vec3 lightV = diffuseLightAmount();
		lightV = combineLight(lightV,ambientLight);
		finalCol = finalCol * lightV;
	}
	finalColorForOutput = vec4(finalCol,1);
}