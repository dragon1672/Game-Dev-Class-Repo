#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

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

class GameInstance {
	SingleKeyManager ComplexBoundsKey;
	SingleKeyManager SimpleBoundsKey;
	SingleKeyManager PauseButton;
	bool isPaused;
	
	int width;
	int height;

	TargetMouse mousePos;
	TargetMouse worldMousePos;

	SimpleBoundary  simpleBounds;
	ComplexBoundary complexBounds;
	Boundary *currentBounds;

	//graphics
	MyGraphics myGraphic;
	OffsetGraphic gameSpaceGraphic;
	
	//interfaces
	HUD hud;
	GameSpace myWorld;
	
	Core::RGB getWorldColor();
	void setStaticBounds();
	void setDynamicBounds();
	void initSimpleBounds();
	void updateCurrentBounds();
public:
	GameInstance (int width, int height);
	bool update(float dt);
	void draw(Core::Graphics& graphics);
	DynamicPosition *getMouse();
	DynamicPosition *getWorldMouse();
};


#endif