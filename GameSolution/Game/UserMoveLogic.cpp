#include "UserMoveLogic.h"
#include "PlayerControls.h"



void UserMoveLogic::init(GameEntity *parent, float rotationAcc, float thrustAcc) {
	this->rotationAcc = rotationAcc;
	this->thrustAcc   = thrustAcc;
	this->parent      = parent;
}
Vector2D UserMoveLogic::getAcc(float dt) {
	Vector2D ret;
#ifdef DEBUG_USER_MOVE_LOGIC
	if(Core::Input::IsPressed( Core::Input::KEY_UP        )) return dt * (-Vector2D(0,ACC));
	if(Core::Input::IsPressed( Core::Input::KEY_DOWN      )) return dt * ( Vector2D(0,ACC));
	if(Core::Input::IsPressed( Core::Input::KEY_LEFT      )) return dt * (-Vector2D(ACC,0));
	if(Core::Input::IsPressed( Core::Input::KEY_RIGHT     )) return dt * ( Vector2D(ACC,0));
#endif
	if(Core::Input::IsPressed( PlayerControls::accelerate )) ret = ret + dt * (parent->getRotationMat() * -Vector2D(0,thrustAcc));
	if(Core::Input::IsPressed( PlayerControls::decelerate )) ret = ret + dt * (parent->getRotationMat() *  Vector2D(0,thrustAcc));
	return ret;
}
bool     UserMoveLogic::hasThrust() {
	return Core::Input::IsPressed( PlayerControls::accelerate );
}
Matrix3D UserMoveLogic::rotation(float dt) {
	if(Core::Input::IsPressed(PlayerControls::rotateLeft)) {
		 angle -= rotationAcc*dt;
	}
	if(Core::Input::IsPressed(PlayerControls::rotateRight)) {
		angle += rotationAcc*dt;
	}
	return Matrix3D::rotationMatrix(angle);
}