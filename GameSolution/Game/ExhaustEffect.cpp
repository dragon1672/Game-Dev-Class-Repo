//*
#include "ExhaustEffect.h"
#include "MyRandom.h"
#include "Partical.h"
#include "ExtendedGraphics.h"

using ExtendedGraphics::randomColor;

void ExhaustEffect::init(GameEntity *parent, float lifetime, float varianceAngle) {
	this->parent = parent;
	this->lifetime = lifetime;
	this->varianceAngle = varianceAngle;
}
//overloads
void ExhaustEffect::initPartical(Partical *toInit) {
	float velSpeed = Random::randomFloat(defaulMinVel,5);
	toInit->vel = Matrix3D::rotationMatrix(Random::randomFloat(-varianceAngle,varianceAngle)) * Vector2D(0,velSpeed);
	toInit->vel = parent->getRotationMat() * toInit->vel;
	toInit->pos = parent->getTransMatrix() * Vector2D(0,parent->getStyle()->getMaxY());//will place at the butt of the ship
	toInit->lifetime = Random::randomFloat(lifetime-.5f,lifetime);
	toInit->color = randomColor();
}
void ExhaustEffect::update(float dt, Partical *toUpdate) {
	toUpdate->lifetime -= dt;
	toUpdate->pos = toUpdate->pos + toUpdate->vel;
	if(toUpdate->lifetime<.1) initPartical(toUpdate);//refresh partical
}
void ExhaustEffect::draw(Core::Graphics graphics, Partical *toUpdate) {
	Vector2D start = toUpdate->pos;
	Vector2D end   = toUpdate->pos + toUpdate->vel.normalized();
	graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
}
//*/