//*
#pragma once
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "Matrix3D.h"
#include "Core.h"
#include "Shape.h"

class GameEntity {
public:
	virtual Shape* getStyle();
	virtual Matrix3D getTransMatrix();
	virtual void update(float dt);
	virtual void draw(Core::Graphics& graphics);
};

#endif
//*/