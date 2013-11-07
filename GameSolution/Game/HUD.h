#pragma once
#include "Core.h"
#include "Vector 2.h"

class HUD {
	int screenWith;
	int screenHeight;
	float pad;
	float addLeftPad;
	float addRightPad;
	float addTopPad;
	float addBotPad;
	float worldWidth;
	float worldHeight;
public:
	HUD(int screenWidth, int screenHeight) : screenWith(screenWith), screenHeight(screenHeight) {
		pad = 20;
		addLeftPad  = 0;
		addRightPad = 0;
		addTopPad   = 40;
		addBotPad   = 0;
		worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
		worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
	}
	void draw(Core::Graphics graphics) {
		graphics.SetColor(RGB(200,200,0));
		graphics.DrawString(10,10,"Welcome to SpaceWars!");
		graphics.DrawString(200,15,"Controls:");
		graphics.DrawString(270,3, "'arrow keys' = Accelerate Ship");
		graphics.DrawString(270,13,"'Shift' = Brake");
		graphics.DrawString(570,3, "'Z' = Ignore Bounds and Warp");
		graphics.DrawString(570,13,"'X' = Ignore Bounds and Bounce");
		graphics.DrawString(570,23,"Use your mouse to move the Turret");
	}
	Vector2D getWorldoffset() {
		return Vector2D(pad+addLeftPad,pad+addTopPad);
	}
	float getWorldWidth() {
		return worldWidth;
	}
	float getWorldHeight() {
		return worldHeight;
	}
};