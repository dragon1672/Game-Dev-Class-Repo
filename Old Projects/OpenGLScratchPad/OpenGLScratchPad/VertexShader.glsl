#version 400

in layout(location=0) vec2 pos;

out vec3 outColor;

uniform mat4x4 transformation;
uniform vec3 dominatingColor;

void main() {
	gl_Position = transformation * vec4(pos.x,pos.y,0,1);
	outColor = dominatingColor;
}