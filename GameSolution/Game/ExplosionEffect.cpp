#include "ExplosionEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"
#include "Partical.h"

#include "Shape.h"

using ExtendedGraphics::randomColor;

Shape basicPartical(RGB(10,10,10), 6,
					Vector2D(-2,-2),
					Vector2D( 2, 2),
					Vector2D( 0, 0),
					Vector2D(-2, 2),
					Vector2D( 2,-2),
					Vector2D( 0, 0)
					);

void ExplosionEffect::init(float lifetime, const Vector2D& pos, Core::RGB seedColor) {
	this->lifetime = lifetime;
	this->orgin = pos;
	this->seedColor = seedColor;
}

void ExplosionEffect::initPartical(Partical *toInit) {
	toInit->pos = orgin;
	toInit->vel = Random::randomUnitVector() * Random::randomFloat(defaulMinVel,defaulMaxVel);
	toInit->lifetime = Random::randomFloat(lifetime-.5f,lifetime);
	toInit->color = ExtendedGraphics::varyColor(seedColor,100);
}
void ExplosionEffect::update(float dt,Partical *toUpdate) {
	toUpdate->pos = toUpdate->pos + dt * toUpdate->vel;
	toUpdate->lifetime -= dt;
	if(toUpdate->lifetime<1) toUpdate->color = ExtendedGraphics::brightness(toUpdate->color,toUpdate->lifetime+.2f);
}
void ExplosionEffect::draw(Core::Graphics graphics, Partical *toDraw) {
	graphics.SetColor(toDraw->color);
	basicPartical.setColor(toDraw->color);
	basicPartical.draw(graphics,toDraw->pos);
	//graphics.DrawLine(toDraw->pos.getX(), toDraw->pos.getY(),toDraw->pos.getX()+1,toDraw->pos.getY()+1);
}