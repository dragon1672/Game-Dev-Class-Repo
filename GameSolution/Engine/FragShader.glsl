#version 400

in vec4 outColor;
in vec3 outPos;
in vec3 outNorm;
in vec2 outUv;
out vec4 finalColorForOutput;

//mats
uniform mat3x3 model2RotationTransform;

//options
uniform bool  diffuseInFrag;
uniform bool  passThrough;
uniform bool  enableTexture;
uniform bool  enableLighting;

//lighting data
uniform vec3  ambientLight;
uniform vec3  diffuseLight;
uniform vec3  diffusePos;

uniform float specPower;
uniform vec3  specColor;
uniform vec3  camPos;

//texture
uniform sampler2D myTexture;



//repeated calculations
vec3 rotatedNormal; // the 'real' normal
vec3 diffuseVector; // vector between point and light
vec3 eyeVector;     // vector between point and camera
vec3 specVector;    // vector of Spec Reflection (aka diffuse reflection)

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
	float cosAngle = clamp(dot(eyeVector,specVector),0,1);
	float specCoeff = pow(cosAngle,specPower);
	return specCoeff * specColor;
}

vec3 combineLight(vec3 one, vec3 two) {
	//return one + two;
	float x = max(one.x , two.x);
	float y = max(one.y , two.y);
	float z = max(one.z , two.z);
	return vec3(x,y,z);
}

void main() {
	vec3 finalCol = vec3(outColor);
	if(!passThrough) {
		if(diffuseInFrag && enableLighting) {
			vec3 lightV;
			calculateVectors(vec3(outPos));
			lightV = diffuseLightAmount();
			lightV = combineLight(lightV,ambientLight);
			finalCol = finalCol * lightV + specLight();
		}
		if(enableTexture) {
			finalCol = finalCol * vec3(texture(myTexture, outUv));
		}
	}
	finalColorForOutput = vec4(finalCol,1);
}