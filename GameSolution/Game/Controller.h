#pragma once
#ifndef Controller_H
#define Controller_H
#include "Boundary.h"
#include "SimpleBounary.h"
#include "ComplexBoundary.h"

#include "SingleKeyManager.h"
#include "TargetMouse.h"

#include "HUD.h"
#include "Vector 2.h"
#include "GameSpace.h"

#include "MyGraphics.h"
#include "OffsetGraphic.h"

#ifdef DEBUG_Controller
	#include "Timer.h"
#endif//DEBUG_Controller

class Controller {
	SingleKeyManager ComplexBoundsKey;
	SingleKeyManager SimpleBoundsKey;
	SingleKeyManager PauseButton;
	bool isPaused;
	
	int width;
	int height;

	TargetMouse mousePos;
	TargetMouse worldMousePos;

	HUD hud;
	GameSpace myWorld;
	SimpleBoundary  simpleBounds;
	ComplexBoundary complexBounds;
	Boundary *currentBounds;
	MyGraphics myGraphic;
	OffsetGraphic gameSpaceGraphic;
	
	Core::RGB getWorldColor();
#ifdef DEBUG_Controller
	Timer FPS_clock;
	float FPS_clock_storage;
	int FPS;
#endif//DEBUG_Controller
	void setStaticBounds();
	void setDynamicBounds();
	void initSimpleBounds();
	void updateCurrentBounds();
public:
	Controller (int width, int height);
	bool update(float dt);
	void draw(Core::Graphics& graphics);
	DynamicPosition *getMouse();
	DynamicPosition *getWorldMouse();
};


#endif