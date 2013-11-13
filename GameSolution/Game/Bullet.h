#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"

struct Bullet {
public:
	Vector2D pos;
	Vector2D vel;
	Shape *style;
	int team;
	float rotation;//amount currentRotation increments
	Matrix3D rotationMat;//current rotation matrix
	Bullet(const Vector2D& pos=Vector2D(0,0), const Vector2D& vel=Vector2D(0,0), Shape *style=NULL, float rotation=0, int team=0) {
		this->pos       = pos;
		this->vel       = vel;
		this->style     = style;
		this->team      = team;
	}
	inline void update(float dt) {
		rotationMat = rotationMat*Matrix3D::rotationMatrix(rotation*dt);
		pos = pos + vel*dt;
	}
	inline void draw(Core::Graphics graphics) {
		Matrix3D transform = Matrix3D::translate(pos) * rotationMat;
		style->draw(graphics,transform);
	}
};

#endif