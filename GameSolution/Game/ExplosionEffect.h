#pragma once
#ifndef EXPLOSION_EFFECT_H
#define EXPLOSION_EFFECT_H

#include "ParticalEffect.h"
#include "ExtendedGraphics.h"

class ExplosionEffect : public ParticalEffect {
private:
	float lifetime;
	float size;
	Vector2D orgin;
	Core::RGB seedColor;
public:
	void init(float lifetime, const Vector2D& pos, Core::RGB seedColor = ExtendedGraphics::randomColor());
	//overloads
	void initPartical(Partical *toInit);
	void update(float dt, Partical *toUpdate);
	void draw(MyGraphics& graphics, Partical *toDraw);
};

#endif