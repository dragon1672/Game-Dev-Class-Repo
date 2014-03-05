#include "TargetShipMoveLogic.h"

Vector2D TargetShipMoveLogic::getDirectionVector() {
	return(target->getPos() - parent->getPos()).normalized();
}
void     TargetShipMoveLogic::init(GameEntity *parent, DynamicPosition *target,float thrustAcc) {
	this->parent    = parent;
	this->target    = target;
	this->thrustAcc = thrustAcc;
}
Vector2D TargetShipMoveLogic::getAcc(float dt) {
	return dt * thrustAcc * getDirectionVector();
}
bool     TargetShipMoveLogic::hasThrust() {
	return true;
}
Matrix3D TargetShipMoveLogic::rotation(float dt) {
	dt;
	return Matrix3D::rotateToVector(getDirectionVector());
}