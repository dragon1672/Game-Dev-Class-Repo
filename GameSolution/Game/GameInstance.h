#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include "View.h"

#include "Boundary.h"
#include "SimpleBounary.h"
#include "ComplexBoundary.h"

#include "SingleKeyManager.h"
#include "TargetMouse.h"

#include "HUD.h"
#include "Vector 2.h"
#include "GameSpace.h"
#include "EndGameView.h"

#include "MyGraphics.h"
#include "OffsetGraphic.h"

#include "ScoreManager.h"

class GameInstance : public View {
	SingleKeyManager ComplexBoundsKey;
	SingleKeyManager SimpleBoundsKey;
	SingleKeyManager PauseButton;
	bool isPaused;
	bool gameOver;
	
	int width;
	int height;

	TargetMouse mousePos;
	TargetMouse worldMousePos;

	SimpleBoundary  simpleBounds;
	ComplexBoundary complexBounds;
	Boundary *currentBounds;

	//graphics
	OffsetGraphic gameSpaceGraphic;

	ScoreManager scoreKeeper;
	EndGameView  gameOverScreen;
	
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
	void draw(MyGraphics& graphics);
	DynamicPosition *getMouse();
	DynamicPosition *getWorldMouse();
};


#endif