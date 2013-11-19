#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"
#include "GameEntity.h"

class Bullet : public GameEntity {
public:
	//gameEntity
	virtual Shape*   getStyle()=0;
	virtual Matrix3D getTransMatrix()=0;
	virtual void     update(float dt)=0;
	//other Core
	virtual void  shutdown()=0;
	virtual bool  isActive()=0;
	virtual int   getTeam()=0;
	virtual float getDamageAmount()=0;
	
	inline void draw(Core::Graphics& graphics) {
		getStyle()->draw(graphics,getTransMatrix());
	}

};

#endif