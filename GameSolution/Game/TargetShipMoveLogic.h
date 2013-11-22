#pragma once
#ifndef TARGET_SHIP_MOVE_LOGIC_H
#define TARGET_SHIP_MOVE_LOGIC_H

#include "MoveLogic.h"
#include "GameEntity.h"

class TargetShipMoveLogic : public MoveLogic {
private:
	GameEntity *parent;
	DynamicPosition *target;
	float thrustAcc;
	Vector2D getDirectionVector();
public:
	TargetShipMoveLogic() { ; }
	TargetShipMoveLogic(GameEntity* parent, DynamicPosition *target,float thrustAcc) {
		init(parent,target,thrustAcc);
	}
	void init(GameEntity *parent, DynamicPosition *target,float thrustAcc);
	Vector2D getAcc(float dt);
	bool     hasThrust();
	Matrix3D rotation(float dt);
};

#endif