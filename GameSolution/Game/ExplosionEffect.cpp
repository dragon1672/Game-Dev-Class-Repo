/*
#include "ExplosionEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"

using ExtendedGraphics::randomColor;

void ExplosionEffect::init(float lifetime, const Vector2D& pos) {
	this->lifetime = lifetime;
	this->orgin = pos;
}

void ExplosionEffect::initPartical(Partical *toInit) {
	toInit->pos = orgin;
	toInit->vel = Random::randomUnitVector() * Random::randomFloat(defaulMinVel,defaulMaxVel);
	toInit->lifetime = Random::randomFloat(lifetime-1,lifetime);
	toInit->color = randomColor();
}
void ExplosionEffect::update(float dt,Partical *toUpdate) {
	toUpdate->pos = toUpdate->pos + dt * toUpdate->vel;
}
void ExplosionEffect::draw(Core::Graphics graphics, Partical *toDraw) {
	if(toDraw->lifetime>0) {
		int r = (int)(GetRValue(toDraw->color) * toDraw->lifetime) % 255;
		int g = (int)(GetGValue(toDraw->color) * toDraw->lifetime) % 255;
		int b = (int)(GetBValue(toDraw->color) * toDraw->lifetime) % 255;
		graphics.SetColor(RGB(r,g,b));
		graphics.DrawLine(toDraw->pos.getX(), toDraw->pos.getY(),toDraw->pos.getX()+1,toDraw->pos.getY()+1);
	}
}
//*/