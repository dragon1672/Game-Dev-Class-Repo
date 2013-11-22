#pragma once
#ifndef MOVE_LOGIC_H
#define MOVE_LOGIC_H

#include "Vector 2.h"

class MoveLogic {
public:
	virtual Vector2D getAcc(float dt)=0;
	virtual bool     hasThrust()=0;
	virtual float    angleAcc(float dt)=0;
	inline Vector2D  brake(const Vector2D& vel, float brakePower) {
		float newX = 0;
		float current = vel.getX();
		if(current!=0) {
			float toSub = (current>0)? brakePower : -brakePower ;
			newX = (abs(toSub)<abs(current))? current-toSub: 0;
		}
		float newY = 0;
		current = vel.getY();
		if(current!=0) {
			float toSub = (current>0)? brakePower : -brakePower ;
			newY = (abs(toSub)<abs(current))? current-toSub: 0;
		}
		return Vector2D(newX,newY);
	}
};

#endif