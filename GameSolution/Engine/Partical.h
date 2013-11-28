#pragma once
#ifndef PARTICAL_H
#define PARTICAL_H

#include "GameGlobal.h"

#include "Vector 2.h"
#include "Core.h"
#include "ParticalEffect.h"

class Partical {
public:
	Vector2D pos;
	Vector2D vel;
	Core::RGB color;
	float lifetime;
	bool paused;
	ParticalEffect *myEffect;
	inline void update(float dt) {
		myEffect->update(dt,this);
	}
	inline void draw(MyGraphics& graphics) {
		myEffect->draw(graphics,this);
	}
};

#endif