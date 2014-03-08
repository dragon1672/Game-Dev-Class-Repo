#version 400

//Line Shader

in layout(location=0) vec3 pos;
in layout(location=1) vec4 col;

out vec4 outColor;

//mats
uniform mat4x4 viewTransform;

uniform vec3  start;
uniform vec3  end;
uniform vec4  overrideColor;
uniform bool  enableOverrideColor;

void main() {
	vec3 posToDraw = (pos.x==0) ? start : end;
	gl_Position =  viewTransform * vec4(posToDraw,1);
	//gl_Position =  vec4(pos.x,pos.y,pos.z,1);
	outColor = enableOverrideColor? col : overrideColor * col;
}