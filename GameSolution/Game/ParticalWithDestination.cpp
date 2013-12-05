#include "ParticalWithDestination.h"


float ParticalWithDestination::PARTICAL_SPEED = 100;

void ParticalWithDestination::updateVelToPos(Vector2D& newTarget) {
	float marginOfError = 2;
	vel = (newTarget - pos);
	if(vel.lengthSquared() > marginOfError * marginOfError)
		if(!slowAtRange || vel.lengthSquared() >= PARTICAL_SPEED * PARTICAL_SPEED)
			vel = PARTICAL_SPEED * vel.normalized();
}

void ParticalWithDestination::updateVelToTarget() {
	updateVelToPos(target);
}

void ParticalWithDestination::update(float dt) {
	pos = pos + dt * vel;
}