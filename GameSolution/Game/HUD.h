#pragma once
#include "Core.h"
#include "Vector 2.h"
#include "MyGraphics.h"

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
	static Core::RGB defaultTextColor;
	HUD(int screenWidth, int screenHeight);
	void     draw(MyGraphics& graphics);
	Vector2D getWorldoffset();
	float    getWorldWidth();
	float    getWorldHeight();
	void HUD::paintWorld(MyGraphics& graphics, Core::RGB color);
	void HUD::worldPopup(MyGraphics& graphics, char* text,Core::RGB color, int width=500, int height=100);
};