#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "LivingGameEntity.h"
#include "DynamicPosition.h"

class Enemy : public LivingGameEntity, DynamicPosition {
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
	int  getTeam()=0;
	Vector2D getPos();
}