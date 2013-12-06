#include "ExplosionEffect.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"
#include "Partical.h"
#include "myAssert.h"
#include "GameMacros.h"
#include "MyGraphics.h"
#include "Shape.h"
#include "LogManager.h"
using ExtendedGraphics::randomColor;

/*
Shape basicPartical(RGB(10,10,10), 6,
					Vector2D(-2,-2),
					Vector2D( 2, 2),
					Vector2D( 0, 0),
					Vector2D(-2, 2),
					Vector2D( 2,-2),
					Vector2D( 0, 0)
					);
//*/
Vector2D basicPartical[] = {
					Vector2D(-2,-2),	Vector2D( 2, 2),//line 1
					Vector2D(-2, 2),	Vector2D( 2,-2),//line 2
};

void ExplosionEffect::init(float lifetime, const Vector2D& pos, Core::RGB seedColor) {
	this->lifetime = lifetime;
	this->orgin = pos;
	this->seedColor = seedColor;
}

void ExplosionEffect::initPartical(Partical *toInit) {
	toInit->pos = orgin;
	toInit->vel = Random::randomUnitVector() * Random::randomFloat(defaulMinVel,defaulMaxVel);
	toInit->lifetime = Random::randomFloat(lifetime-.5f,lifetime);
	toInit->color = ExtendedGraphics::varyColor(seedColor,20);
}
void ExplosionEffect::update(float dt,Partical *toUpdate) {
	LOG(Severe,"Partical are updateing OMG",0);
	toUpdate->pos = toUpdate->pos + dt * toUpdate->vel;
	toUpdate->lifetime -= dt;
	if(toUpdate->lifetime<1) toUpdate->color = ExtendedGraphics::brightness(toUpdate->color,toUpdate->lifetime+.2f);
}
void ExplosionEffect::draw(MyGraphics& graphics, Partical *toDraw) {
	graphics.setColor(toDraw->color);
	ASSERT(SIZE_OF_ARRAY(basicPartical)%2==0,"Even number of points required for drawing set of lines");
	for(int i=0;i<SIZE_OF_ARRAY(basicPartical);i+=2) {
		Vector2D p1 = toDraw->pos + basicPartical[i];
		Vector2D p2 = toDraw->pos + basicPartical[i+1];
		graphics.drawLine(p1,p2);
	}
}