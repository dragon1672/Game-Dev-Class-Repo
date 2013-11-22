#pragma once
#ifndef ENEMY_KAMIKAZE_H
#define ENEMY_KAMIKAZE_H

#include "LivingGameEntity.h"

class EnemyKamikaze : public LivingGameEntity{
private:
	static const float MAX_SPEED;
	Vector2D pos;
	float angle;

public:

	//overloading
	Shape* getStyle();
	Matrix3D getTransMatrix();
	Matrix3D getRotationMat();
	void update(float dt);
	void draw(Core::Graphics& graphics);
	int  getTeam();
	Vector2D getPos();
};

#endif