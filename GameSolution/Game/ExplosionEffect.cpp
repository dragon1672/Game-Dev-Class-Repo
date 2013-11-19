//*
#include "ExplosionEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"
#include "Partical.h"

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
	if(toUpdate->lifetime<1) toUpdate->color = ExtendedGraphics::brightness(toUpdate->color,toUpdate->lifetime);
}
void ExplosionEffect::draw(Core::Graphics graphics, Partical *toDraw) {
	graphics.SetColor(toDraw->color);
	graphics.DrawLine(toDraw->pos.getX(), toDraw->pos.getY(),toDraw->pos.getX()+1,toDraw->pos.getY()+1);
}
//*/