#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec4 col;
in layout(location=2) vec3 norm;

out vec4 outColor;

uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;
uniform bool diffuseInFrag;

uniform bool passThrough;

uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 diffusePos;

vec3 diffuseLightAmount(vec4 vertPos) {
	vec3 diff = diffusePos - vec3(vertPos);
	diff = normalize(diff);
	vec3 rotatedNorm = normalize(mat3(model2WorldTransform) * norm);
	return dot(rotatedNorm,diff) * diffuseLight;
}

vec3 combineLight(vec3 diffuse, vec3 amb) {
	return diffuse + amb;
}

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	
	vec3 finalCol = vec3(col);
	if(!passThrough) {
		vec3 lightV;
		//if(!diffuseInFrag) // not currently supported
			lightV = diffuseLightAmount(transformedPos);
		lightV = combineLight(lightV,ambientLight);
		finalCol = vec3(col) * lightV;
	}
	outColor = vec4(finalCol,1);
}