#pragma once
#include "Core.h"
#include "Vector 2.h"

class HUD {
	int screenWith;
	int screenHeight;
	const int pad = 5;
	const int addLeftPad  = 10;
	const int addRightPad = 0;
	const int addTopPad   = 30;
	const int addBotPad   = 0;
	int worldWidth;
	int worldHeight;
public:
	HUD(int screenWidth, int screenHeight) : screenWith(screenWith), screenHeight(screenHeight) {
		worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
		worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
	}
	void draw(Core::Graphics graphics) {

	}
	Vector2D getWorldoffset() {
		return Vector2D(pad+addRightPad,pad+addTopPad);
	}
	int getWorldWidth() {
		return worldWidth;
	}
	int getWorldHeight() {
		return worldHeight;
	}
};