#include "DynamicPosRandom.h"
#include "MyRandom.h"

void DynamicPosRandom::init(float width, float height) {
	this->width  = width;
	this->height = height;
}
Vector2D DynamicPosRandom::getPos() {
	return Random::randomFloatVectorInBox(width,height);
}