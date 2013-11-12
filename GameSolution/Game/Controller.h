#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Boundary.h"
#include "HUD.h"
#include "Vector 2.h"
#include "GameSpace.h"

#define DEBUG_CONTROLLER

#ifdef DEBUG_CONTROLLER
#include <sstream>
#endif//DEBUG_CONTROLLER


class Controller {
	int width;
	int height;
	HUD hud;
	GameSpace myWorld;
	Boundary bounds;
#ifdef DEBUG_CONTROLLER
	int FPS;
#endif//DEBUG_CONTROLLER
	void setStaticBounds();
	void setDynamicBounds();
public:
	Controller (int width, int height);
	bool update(float dt);
	void draw(Core::Graphics& graphics);
};


#endif