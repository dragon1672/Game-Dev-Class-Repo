#pragma once
#ifndef VELOCITY_BASED_LIVING_ENTITY_H
#define VELOCITY_BASED_LIVING_ENTITY_H

#include "LivingGameEntity.h"

class VelocityBasedLivingEntity : LivingGameEntity {
protected:
	Vector2D vel;
	Vector2D pos;
	float mass;
public:
	VelocityBasedLivingEntity() {
		mass = getMass();
	}
	virtual int getMass()=0;
	void addAcc(Vector2D& acc) {//scale needs to already be applied
		vel = vel + acc;
	}
	virtual void collideWithEntity(VelocityBasedLivingEntity * that) {
		LivingGameEntity::collisionDamage(that);
	}
};

#endif