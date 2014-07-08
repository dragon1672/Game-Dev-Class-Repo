#version 400

//PassThrough FragShader

in vec2 outUv;

uniform sampler2D normalMap;
uniform vec3 lightPosition
uniform vec3 lightColor
uniform vec3 specPower

void main() {
	gl_FragColor = texture(myTexture, outUv) + vec4(0,0,0,1);
}