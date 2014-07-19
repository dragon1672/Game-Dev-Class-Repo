#version 400

in vec2 outUv;
in vec3 outNorm;
in vec3 outPos;

out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform vec2 uvOffset;

uniform vec3  lightColor;
uniform vec3  diffusePos;
uniform float specPower;
uniform vec3  camPos;


//repeated calculations
vec3 rotatedNormal; // the 'real' normal
vec3 diffuseVector; // vector between point and light
vec3 eyeVector;     // vector between point and camera
vec3 specVector;    // vector of Spec Reflection (aka diffuse reflection)

void calculateVectors(vec3 vertPos) {
	rotatedNormal = normalize(outNorm);
	diffuseVector = normalize(diffusePos - vertPos);
	eyeVector = normalize(camPos - vertPos);
	specVector = -reflect(diffuseVector,rotatedNormal);
}
vec3 diffuseLightAmount() {
	return dot(rotatedNormal,diffuseVector) * lightColor;
}
vec3 specLight() {
	float cosAngle = clamp(dot(eyeVector,specVector),0,1);
	float specCoeff = pow(cosAngle,specPower);
	return specCoeff * lightColor;
}

vec3 combineLight(vec3 one, vec3 two) {
	//return one + two;
	float x = max(one.x , two.x);
	float y = max(one.y , two.y);
	float z = max(one.z , two.z);
	return vec3(x,y,z);
}

void main() {
	vec3 finalCol = texture(myTexture,uvOffset+outUv).ggg;
	finalCol = vec3(1,1,1);
	vec3 lightV;
	calculateVectors(vec3(outPos));
	lightV = diffuseLightAmount();
	finalCol = finalCol * lightV + specLight();
	finalColor = vec4(finalCol,1);
	//finalColor = vec4(1,1,1,1);
}