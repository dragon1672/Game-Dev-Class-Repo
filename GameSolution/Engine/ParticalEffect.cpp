#include "ParticalEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"

using ExtendedGraphics::randomColor;



void ParticalEffect::init(int size, const Vector2D& pos, float lifetime) {
	assert(size<MAX_PARTICALS);
	numParticals = size;
	for(int i=0;i<numParticals; i++) {
		particals[i].pos = pos;
		particals[i].vel = Random::randomUnitVector() * Random::randomFloat(5,100);
		particals[i].lifetime = Random::randomFloat(lifetime-1,lifetime);
		particals[i].color = randomColor();
	}
}
void ParticalEffect::update(float dt) {
	for(int i=0;i<numParticals; i++) {
		if(particals[i].lifetime>0)
			particals[i].update(dt);
	}
}
void ParticalEffect::draw(Core::Graphics graphics) {
	for(int i=0;i<numParticals; i++) {
		if(particals[i].lifetime>0) {
			graphics.SetColor(particals[i].color);
			graphics.DrawLine(particals[i].pos.getX(), particals[i].pos.getY(),particals[i].pos.getX()+1,particals[i].pos.getY()+1);
		}
	}
}