#pragma once
#include "Core.h"
#include "Vector 2.h"

class HUD {
	int   screenWith;
	int   screenHeight;
	float pad;
	float addLeftPad;
	float addRightPad;
	float addTopPad;
	float addBotPad;
	float worldWidth;
	float worldHeight;
public:
	HUD(int screenWidth, int screenHeight);
	void     draw(Core::Graphics& graphics);
	Vector2D getWorldoffset();
	float    getWorldWidth();
	float    getWorldHeight();
};