#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec3 col;

out vec3 outColor;

uniform mat4x4 transformation;

void main() {
	gl_Position = transformation * vec4(pos.x,pos.y,pos.z,1);
	outColor = col;
}