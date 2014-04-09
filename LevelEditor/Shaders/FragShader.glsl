#version 400

//PassThrough FragShader

in vec4 outColor;
in vec2 outUv;

uniform sampler2D myTexture;

void main() {
	gl_FragColor = texture(myTexture, outUv);
}