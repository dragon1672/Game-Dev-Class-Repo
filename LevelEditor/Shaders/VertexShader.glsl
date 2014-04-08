#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec4 col;
in layout(location=2) vec3 norm;
in layout(location=3) vec2 uv;

out vec4 outColor;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outColor = col;
}