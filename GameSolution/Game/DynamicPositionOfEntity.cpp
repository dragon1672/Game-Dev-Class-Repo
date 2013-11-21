#include "DynamicPositionOfEntity.h"

void     DynamicPositionOfEntity::setTarget(GameEntity *toWatch) {
	target = toWatch;
}
Vector2D DynamicPositionOfEntity::getPos() {
	return target->getTransMatrix() * Vector2D(0,0);
}