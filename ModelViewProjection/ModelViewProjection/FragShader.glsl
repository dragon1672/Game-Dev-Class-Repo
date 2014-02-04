#version 400

in vec4 outColor;
in vec3 outPos;
in vec3 outNorm;
out vec4 finalColorForOutput;

//mats
uniform mat3x3 model2RotationTransform;

//options
uniform bool  diffuseInFrag;
uniform bool  passThrough;

//lighting data
uniform vec3  ambientLight;
uniform vec3  diffuseLight;
uniform vec3  diffusePos;

uniform float specPower;
uniform vec3  specColor;
uniform vec3  camPos;



//repeated calculations
vec3 rotatedNormal; // the 'real' normal
vec3 diffuseVector; // vector between point and light
vec3 eyeVector;     // vector between point and camera
vec3 specVector;    // vector of Spec Reflection (aka diffuse reflection)

float greatestNum(float a, float b) {
	return (a > b)? a : b;
}

void calculateVectors(vec3 vertPos) {
	rotatedNormal = model2RotationTransform * normalize(outNorm);
	diffuseVector = normalize(diffusePos - vertPos);
	eyeVector = normalize(camPos - vertPos);
	specVector = -reflect(diffuseVector,rotatedNormal);
}
vec3 diffuseLightAmount() {
	return dot(rotatedNormal,diffuseVector) * diffuseLight;
}
vec3 specLight() {
	float cosAngle = greatestNum(0,dot(eyeVector,specVector));
	float specCoeff = pow(cosAngle,specPower);
	return specCoeff * specColor;
}

vec3 combineLight(vec3 one, vec3 two) {
	//return one + two;
	float x = greatestNum(one.x , two.x);
	float y = greatestNum(one.y , two.y);
	float z = greatestNum(one.z , two.z);
	return vec3(x,y,z);
}

void main() {
	vec3 finalCol = vec3(outColor);
	if(diffuseInFrag && !passThrough) {
		vec3 lightV;
		calculateVectors(vec3(outPos));
		lightV = diffuseLightAmount();
		lightV = combineLight(lightV,ambientLight);
		finalCol = finalCol * lightV + specLight();
	}
	finalColorForOutput = vec4(finalCol,1);
}