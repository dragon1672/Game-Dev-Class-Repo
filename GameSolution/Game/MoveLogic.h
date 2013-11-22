#pragma once
#ifndef MOVE_LOGIC_H
#define MOVE_LOGIC_H

#include "Vector 2.h"

class MoveLogic {
public:
	virtual Vector2D getAcc(float dt)=0;
	virtual bool     hasThrust()=0;
	virtual float    angleAcc(float dt)=0;
	Vector2D  brake(const Vector2D& vel, float brakePower);
};

#endif