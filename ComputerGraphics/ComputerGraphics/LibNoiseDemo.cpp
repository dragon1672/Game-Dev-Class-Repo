#include "LibNoiseDemo.h"

#include <noise\noise.h>
#include "noiseutils.h"
#include <Engine\unsigned.h>

void LibNoise::init() {
	noise::module::Perlin myModule;
	//myModule.SetOctaveCount(1);
	//myModule.SetFrequency(1.0);

	double ds[5];
	for (int i = 0; i < sizeof(ds) / sizeof(*ds); i++)
	{
		ds[i] = myModule.GetValue(i,i,i);
	}

	const uint BYTES_PER_COLOR = 4;
	const uint width = 2;
	const uint height = 2;
	GLbyte * meTexture = new GLbyte[BYTES_PER_COLOR * width * height];
	meTexture[0x0] = 0xFF;
	meTexture[0x5] = 0xFF;
	meTexture[0xA] = 0xFF;
	meTexture[0xC] = 0xFF;
	meTexture[0xD] = 0xFF;
	meTexture[0xE] = 0xFF;

	double pie = 0;
}

void LibNoise::nextFrame(float dt) {

}