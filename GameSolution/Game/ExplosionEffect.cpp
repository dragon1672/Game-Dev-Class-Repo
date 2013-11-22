#include "ExplosionEffect.h"
#include "MyRandom.h"
#include <cassert>
#include "ExtendedGraphics.h"
#include "Partical.h"

#include "Shape.h"

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
	toUpdate->pos = toUpdate->pos + dt * toUpdate->vel;
	toUpdate->lifetime -= dt;
	if(toUpdate->lifetime<1) toUpdate->color = ExtendedGraphics::brightness(toUpdate->color,toUpdate->lifetime+.2f);
}
void ExplosionEffect::draw(Core::Graphics graphics, Partical *toDraw) {
	graphics.SetColor(toDraw->color);
	//since it is really an array of lines it should have an even length
	MY_ASSERT(SIZE_OF_ARRAY(basicPartical)%2==0);
	for(int i=0;i<SIZE_OF_ARRAY(basicPartical);i+=2) {
		Vector2D p1 = toDraw->pos + basicPartical[i];
		Vector2D p2 = toDraw->pos + basicPartical[i+1];
		graphics.DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
	}
}