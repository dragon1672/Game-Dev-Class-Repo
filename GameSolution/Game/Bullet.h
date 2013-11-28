#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "GameGlobal.h"

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"
#include "ExhaustEffect.h"

class Bullet {
public:
	Vector2D pos;
	Vector2D vel;
	Vector2D velNorm;//this is used for rotation
	Shape *style;
	bool isActive;
	float power;
	int team;
	Bullet(const Vector2D& pos=Vector2D(0,0), const Vector2D& vel=Vector2D(0,0), Shape *style=NULL, int team=0) {
		this->pos       = pos;
		this->style     = style;
		this->team      = team;
		setVel(vel);
	}
	void setVel(const Vector2D& newVel);
	void update(float dt);
	void draw(MyGraphics& graphics);
};

#endif