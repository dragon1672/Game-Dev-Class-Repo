#pragma once
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "Matrix3D.h"
#include "Core.h"
#include "Shape.h"
#include "DynamicPosition.h"

class MyGraphics;

class GameEntity : public DynamicPosition {
public:
	virtual Shape* getStyle();
	virtual Matrix3D getTransMatrix();
	inline virtual Matrix3D getRotationMat() {
		return Matrix3D();
	}
	virtual void update(float dt);
	virtual void draw(MyGraphics& graphics)=0;
	virtual int  getTeam()=0;
	virtual Vector2D getPos()=0;
	//virtual void startup()=0;
	//virtual void shutdown()=0;
};

#endif