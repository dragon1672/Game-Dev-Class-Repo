#version 400

//PassThrough FragShader

uniform bool  ignoreDepthTest;
in vec4 outColor;
out vec4 finalColor;

void main() {
	gl_FragColor = outColor;
	if(ignoreDepthTest) {
		gl_FragDepth = -1;
	}
}