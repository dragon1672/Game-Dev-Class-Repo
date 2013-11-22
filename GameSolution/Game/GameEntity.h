#pragma once
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "GameGlobal.h"
#include "Matrix3D.h"
#include "Core.h"
#include "Shape.h"
#include "DynamicPosition.h"

class GameEntity : public DynamicPosition {
public:
	       virtual Shape* getStyle();
	       virtual Matrix3D getTransMatrix();
	inline virtual Matrix3D getRotationMat() {
		return Matrix3D();
	}
	       virtual void update(float dt);
	       virtual void draw(Core::Graphics& graphics);
		   virtual int  getTeam()=0;
		   virtual Vector2D getPos()=0;
};

#endif