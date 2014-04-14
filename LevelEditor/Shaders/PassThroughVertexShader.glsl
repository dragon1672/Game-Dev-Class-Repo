#version 400

//PassThrough 

in layout(location=0) vec3 pos;
in layout(location=1) vec4 col;

out vec4 outColor;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

uniform vec4  overrideColor;
uniform bool  enableOverrideColor;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outColor = enableOverrideColor? overrideColor : overrideColor * col;
}