#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec4 col;
in layout(location=2) vec3 norm;

out vec4 outColor;
out vec3 outPos;
out vec3 outNorm;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;
uniform mat3x3 model2RotationTransform;

//options
uniform bool  diffuseInFrag;
uniform bool  passThrough;
uniform bool  enableOverrideColor;

//lighting data
uniform vec3  ambientLight;
uniform vec3  diffuseLight;
uniform vec3  diffusePos;
uniform vec3  overrideColor;

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
	rotatedNormal = model2RotationTransform * norm;
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
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	
	outPos = vec3(transformedPos);
	outNorm = norm;
	
	vec3 finalCol = vec3(col);
	if(enableOverrideColor && !passThrough) {
		finalCol = overrideColor;
	}
	if(!diffuseInFrag && !passThrough) {
		vec3 lightV;
		calculateVectors(vec3(transformedPos));
		lightV = diffuseLightAmount();
		lightV = combineLight(lightV,ambientLight);
		finalCol = finalCol * lightV + specLight();
	}
	outColor = vec4(finalCol,1);
}