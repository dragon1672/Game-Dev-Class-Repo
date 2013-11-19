#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "GameGlobal.h"

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"

class Bullet {
public:
	Vector2D pos;
	Vector2D vel;
	Vector2D velNorm;//this is used for direction
	Shape *style;
	int team;
	Bullet(const Vector2D& pos=Vector2D(0,0), const Vector2D& vel=Vector2D(0,0), Shape *style=NULL, int team=0) {
		this->pos       = pos;
		this->style     = style;
		this->team      = team;
		setVel(vel);
	}
	inline void setVel(const Vector2D& newVel) {
		vel = newVel;
		velNorm = vel.normalized();
	}
	inline void update(float dt) {
		pos = pos + vel*dt;
	}
	inline void draw(Core::Graphics graphics) {
		Matrix3D transform = Matrix3D::translate(pos) * Matrix3D::rotateToVector(-velNorm);
		style->draw(graphics,transform);
	}
};

#endif