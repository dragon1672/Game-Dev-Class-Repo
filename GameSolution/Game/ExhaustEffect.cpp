//*
#include "ExhaustEffect.h"
#include "MyRandom.h"
#include "Partical.h"
#include "ExtendedGraphics.h"

using ExtendedGraphics::randomColor;

void ExhaustEffect::init(GameEntity *parent, float lifetime, float varianceAngle) {
	active = true;
	this->parent = parent;
	this->lifetime = lifetime;
	this->varianceAngle = varianceAngle;
}
void ExhaustEffect::shutdown() {
	active = false;
}
//overloads
void ExhaustEffect::initPartical(Partical *toInit) {
	if(active) {
		toInit->lifetime = Random::randomFloat(lifetime-.5f,lifetime);
		if(!paused) {
			float velSpeed = Random::randomFloat(defaulMinVel,5);
			toInit->vel = Matrix3D::rotationMatrix(Random::randomFloat(-varianceAngle,varianceAngle)) * Vector2D(0,velSpeed);
			toInit->vel = parent->getRotationMat() * toInit->vel;
			toInit->pos = parent->getTransMatrix() * Vector2D(0,parent->getStyle()->getMaxY());//will place at the butt of the ship
			toInit->color = ExtendedGraphics::varyColor(RGB(255,0,0),20);
		}
		toInit->paused = paused;
	}
}
void ExhaustEffect::update(float dt, Partical *toUpdate) {
	if(!toUpdate->paused) {
		toUpdate->lifetime -= dt;
		toUpdate->pos = toUpdate->pos + toUpdate->vel;
		if(toUpdate->lifetime<1) toUpdate->color = ExtendedGraphics::addG(toUpdate->color,(int)(255*(dt+.1)));
	}
	if(toUpdate->lifetime<.1 || toUpdate->paused) initPartical(toUpdate);//refresh partical
}
void ExhaustEffect::draw(Core::Graphics graphics, Partical *toUpdate) {
	if(!toUpdate->paused) {
		graphics.SetColor(toUpdate->color);
		Vector2D start = toUpdate->pos;
		Vector2D end   = toUpdate->pos + toUpdate->vel*-1;
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		//creating a square around position and drawing to the same end point
		//this make the partical look larger
		start = toUpdate->pos+Vector2D( 1, 1);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		start = toUpdate->pos+Vector2D(-1, 1);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		start = toUpdate->pos+Vector2D(-1,-1);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		start = toUpdate->pos+Vector2D( 1, -1);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
	}
}
//*/