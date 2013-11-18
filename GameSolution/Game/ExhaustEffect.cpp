/*
#include "ExhaustEffect.h"
#include "MyRandom.h"

void ExhaustEffect::init(GameEntity *parent, int lifetime, float varianceAngle) {
	this->parent = parent;
	this->lifetime = lifetime;
	this->varianceAngle = varianceAngle
}
//overloads
void ExhaustEffect::initPartical(Partical *toInit) {
	float velSpeed = Random::randomFloat(defaulMinVel,defaulMaxVel);
	toInit->vel = Matrix3D::rotationMatrix(Random::randomFloat(-varianceAngle,varianceAngle)) * Vector2D(0,-velSpeed);
	toInit->vel = parent->getRotationMat() * toInit->vel;
	toInit->pos = parent->getTransMatrix;
	toInit->lifetime = Random::randomFloat(lifetime-1,lifetime);
}
void ExhaustEffect::update(float dt, Partical *toUpdate) {
	toUpdate->lifetime -= dt;
	if(toUpdate->lifetime<.1) initPartical(toUpdate);//refresh partical
}
void ExhaustEffect::draw(Core::Graphics graphics, Partical *toUpdate) {
	Vector2D start = toUpdate->pos;
	Vector2D end   = toUpdate->pos + toUpdate->vel;
	graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
}
//*/