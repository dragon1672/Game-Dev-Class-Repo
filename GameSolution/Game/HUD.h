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
	static Core::RGB defaultTextColor;
	HUD(int screenWidth, int screenHeight);
	void     draw(Core::Graphics& graphics);
	Vector2D getWorldoffset();
	float    getWorldWidth();
	float    getWorldHeight();
	void HUD::paintWorld(Core::Graphics graphics, Core::RGB color);
	void HUD::worldPopup(Core::Graphics graphics, char* text,Core::RGB color, int width=500, int height=100);
};