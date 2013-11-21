#pragma once
#ifndef DYNAMIC_POSITION_OF_ENTITY_H
#define DYNAMIC_POSITION_OF_ENTITY_H

#include "DynamicPosition.h"
#include "GameEntity.h"

class DynamicPositionOfEntity : DynamicPosition {
private:
	GameEntity *target;
public:
	DynamicPositionOfEntity() { ; }//so target can be set later
	DynamicPositionOfEntity(GameEntity *toWatch) {
		setTarget(toWatch);
	}
	void setTarget(GameEntity *toWatch);
	Vector2D getPos();
};

#endif