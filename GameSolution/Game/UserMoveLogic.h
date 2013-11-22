#pragma once
#ifndef USER_MOVE_LOGIC_H
#define USER_MOVE_LOGIC_H

#include "MoveLogic.h"
#include "GameEntity.h"

class UserMoveLogic : public MoveLogic {
private:
	float rotationAcc;
	float thrustAcc;
	GameEntity *parent;
	float angle;
public:
	UserMoveLogic() { ; }
	UserMoveLogic(GameEntity *parent, float rotationAcc, float thrustAcc) {
		init(parent,rotationAcc,thrustAcc);
	}
	void init(GameEntity *parent, float rotationAcc, float thrustAcc);
	//overloads
	Vector2D getAcc(float dt);
	bool     hasThrust();
	Matrix3D rotation(float dt);
};

#endif