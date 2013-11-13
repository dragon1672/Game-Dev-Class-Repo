#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"

struct Bullet {
private:
	float currentRotation;
public:
	Vector2D pos;
	Vector2D vel;
	Shape *style;
	float rotation;
	int team;
	Bullet(const Vector2D& pos=Vector2D(0,0), const Vector2D& vel=Vector2D(0,0), Shape *style=NULL, float rotation=20, int team=0) {
		this->pos       = pos;
		this->vel       = vel;
		this->style     = style;
		this->rotation  = rotation;
		this->team      = team;
		currentRotation = 0;
	}
	inline void update(float dt) {
		currentRotation += rotation*dt;
		pos = pos + vel*dt;
	}
	inline void draw(Core::Graphics graphics) {
		style->draw(graphics,pos,currentRotation);
	}
};

#endif