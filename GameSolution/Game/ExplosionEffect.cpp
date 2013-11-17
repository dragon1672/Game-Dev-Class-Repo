#include "ExplosionEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"

using ExtendedGraphics::randomColor;


void ExplosionEffect::init(int size, const Vector2D& pos, float lifetime) {
	assert(size<MAX_PARTICALS);
	numParticals = size;
	for(int i=0;i<numParticals; i++) {
		particals[i].pos = pos;
		particals[i].vel = Random::randomUnitVector() * Random::randomFloat(5,100);
		particals[i].lifetime = Random::randomFloat(lifetime-1,lifetime);
		particals[i].color = randomColor();
	}
}
void ExplosionEffect::update(float dt) {
	for(int i=0;i<numParticals; i++) {
		if(particals[i].lifetime>0)
			particals[i].update(dt);
	}
}
void ExplosionEffect::draw(Core::Graphics graphics) {
	for(int i=0;i<numParticals; i++) {
		if(particals[i].lifetime>0) {
			int r = (int)(GetRValue(particals[i].color) * particals[i].lifetime) % 255;
			int g = (int)(GetGValue(particals[i].color) * particals[i].lifetime) % 255;
			int b = (int)(GetBValue(particals[i].color) * particals[i].lifetime) % 255;
			graphics.SetColor(RGB(r,g,b));
			graphics.DrawLine(particals[i].pos.getX(), particals[i].pos.getY(),particals[i].pos.getX()+1,particals[i].pos.getY()+1);
		}
	}
}