#include "HUD.h"
#include "MyRandom.h"

#define CHAR_SPACING 7//for graphics.drawString()

#ifdef HUD_DEBUG
#include <sstream>

std::string num2str(float num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}
std::string num2str(int num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}
#endif

void drawDottedLine(Core::Graphics& graphics, Vector2D start, Vector2D end, float length) {
	Vector2D line = end - start;
	float lineLength = line.length();
	int steps = lineLength / length;
	float lerpPercent = length / lineLength;
	bool drawing = true;
	float currentStep = 0;

	while((currentStep+lerpPercent)<=1) {
		if(drawing) {
			Vector2D begin = start.LERP(currentStep,end);
			Vector2D stop  = start.LERP(currentStep+lerpPercent,end);
			graphics.DrawLine(begin.getX(),begin.getY(),stop.getX(),stop.getY());
		}
		drawing != drawing;
		currentStep += 2*lerpPercent;
	}
}
void drawRainbowText(Core::Graphics& graphics, float x, float y, char* text) {
	for(int i=0;i<strlen(text);i++) {
		int r = Random::randomInt(0,255);
		int g = Random::randomInt(0,255);
		int b = Random::randomInt(0,255);
		graphics.SetColor(RGB(r,g,b));
		graphics.DrawString(x+i*CHAR_SPACING,y,&text[i]);
	}
}
void dottedLineTest(Core::Graphics& graphics) {
	//*DottedLineTest
	Vector2D start = Vector2D(10,10);
	Vector2D end   = Vector2D(100,100);
	graphics.SetColor(RGB(0,255,0));
	graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
	graphics.SetColor(RGB(100,100,0));
	drawDottedLine(graphics,start,end,5);
	graphics.SetColor(RGB(200,200,0));
	//*/
}

HUD::HUD(int screenWidth, int screenHeight) : screenWith(screenWith), screenHeight(screenHeight) {
	pad = 20;
	addLeftPad  = 0;//80;
	addRightPad = 0;
	addTopPad   = 30;
	addBotPad   = 0;
	worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
	worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
}
void      HUD::draw(Core::Graphics& graphics) {
	//dottedLineTest();
	Core::RGB yellow = RGB(255,255,0);
	graphics.SetColor(yellow);
	//drawRainbowText(graphics,0,0,"This Is A Test");

	//*
	graphics.DrawString(10,10,"Welcome to");
	drawRainbowText(graphics,10,20,"SpaceWars!");
	graphics.SetColor(yellow);
	graphics.DrawString(200,15,"Controls:");
	graphics.DrawString(270,3, "'arrow keys' = Accelerate Ship");
	graphics.DrawString(270,13,"'Shift' = Brake");
	graphics.DrawString(570,3, "'Z' = Ignore Bounds and Warp");
	graphics.DrawString(570,13,"'X' = Ignore Bounds and Bounce");
	graphics.DrawString(570,23,"Use your mouse to move the Turret");
	//*/
}
Vector2D  HUD::getWorldoffset() {
	return Vector2D(pad+addLeftPad,pad+addTopPad);
}
float     HUD::getWorldWidth() {
	return worldWidth;
}
float     HUD::getWorldHeight() {
	return worldHeight;
}