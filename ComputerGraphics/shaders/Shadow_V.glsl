#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec3 col;
in layout(location=2) vec3 norm;
in layout(location=3) vec2 uv;

out vec2 fragUv;
out vec3 fragCol;
out vec3 fragNorm;
out vec3 fragPos;
out vec4 ShadowCoord;

//mats
uniform mat4 perspectiveMat;
uniform mat4 camLookAt;

uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos,1);
	gl_Position =  viewTransform * transformedPos;
	//gl_Position = perspectiveMat * camLookAt * transformedPos;
	fragUv = uv;
	fragCol = col;
	fragNorm = norm;
	fragPos = vec3(transformedPos);
	
	vec4 unbiasTexture = perspectiveMat * camLookAt * transformedPos;
	ShadowCoord = unbiasTexture;
	ShadowCoord /= ShadowCoord.w;
	ShadowCoord.x = (ShadowCoord.x + 1) / 2;
	ShadowCoord.y = (ShadowCoord.y + 1) / 2;
	ShadowCoord.z = (ShadowCoord.z + 1) / 2;
}