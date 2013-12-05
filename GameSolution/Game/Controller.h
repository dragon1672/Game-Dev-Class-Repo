#pragma once
#ifndef Controller_H
#define Controller_H

#include "TargetMouse.h"
#include "MyGraphics.h"

#include "StartScreen.h"
#include "GameInstance.h"

class Controller {
	int width;
	int height;
	TargetMouse mousePos;
	MyGraphics myGraphic;

	static const char* startScreenOptions[];
	StartScreen myStartScreen;
	//views
	GameInstance myGameView;

public:
	Controller (int width, int height);
	bool update(float dt);
	void draw(Core::Graphics& graphics);
	DynamicPosition *getMouse();
};


#endif