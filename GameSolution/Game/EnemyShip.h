#pragma once
#ifndef Enemy_Ship_H
#define Enemy_Ship_H

#include "LivingGameEntity.h"
#include "Vector 2.h"
#include "BasicTurret.h"

class EnemyShip : LivingGameEntity {
	Vector2D pos;
	Vector2D vel;
	BasicTurret myTurret;

	void pointToShip();
public:
	//overloads
	Shape* getStyle();
	Matrix3D getTransMatrix() {
		return Matrix3D::translate(pos);
	}
	Matrix3D getRotationMat() {
		return Matrix3D();
	}
	void update(float dt) {
		pos = pos + dt*vel;
	}
	void draw(Core::Graphics& graphics) {
		getStyle()->draw(graphics,getTransMatrix());
	}
};

#endif