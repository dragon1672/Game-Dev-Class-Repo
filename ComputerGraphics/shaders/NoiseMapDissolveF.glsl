#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform sampler2D noiseMap;
uniform float discardThreshold;

void main() {
	if(texture(noiseMap,outUv).r < discardThreshold) discard;
	finalColor = texture(myTexture,outUv);
	//finalColor = texture(noiseMap,outUv);
	float noise = texture(noiseMap,outUv).r - discardThreshold;
	float startFallOff = .05;
	if(noise < startFallOff) {
		float percent = noise / startFallOff;
		vec4 mixColor = vec4(mix(vec3(0,0,.8), vec3(1,1,0),percent),1);
		finalColor = mix(mixColor,finalColor,.5);
		//finalColor *= vec4((1-percent) * fireEnd + (percent * fireStart),1);
	}
	finalColor.a = 1;
	//finalColor = vec4(discardThreshold*vec3(1,1,1),1);
}