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
	float lineLength = (float)line.length();
	float lerpPercent = length / lineLength;
	bool drawing = true;
	float currentStep = 0;

	while((currentStep+lerpPercent)<=1) {
		if(drawing) {
			Vector2D begin = start.LERP(currentStep,end);
			Vector2D stop  = start.LERP(currentStep+lerpPercent,end);
			graphics.DrawLine(begin.getX(),begin.getY(),stop.getX(),stop.getY());
		}
		drawing = !drawing;
		currentStep += 2*lerpPercent;
	}
}
void drawDottedLine(Core::Graphics& graphics, float x1, float y1, float x2, float y2, float length) {
	drawDottedLine(graphics,Vector2D(x1,y1),Vector2D(x2,y2),length);
}
void drawRainbowText(Core::Graphics& graphics, float x, float y, char* text) {
	for(unsigned int i=0;i<strlen(text);i++) {
		int r = Random::randomInt(0,255);
		int g = Random::randomInt(0,255);
		int b = Random::randomInt(0,255);
		graphics.SetColor(RGB(r,g,b));
		graphics.DrawString((int)x+i*CHAR_SPACING,y,&text[i]);
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
	addLeftPad  = 200-pad;
	addRightPad = 0;
	addTopPad   = 100-pad;
	addBotPad   = 0;
	worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
	worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
}
void      HUD::draw(Core::Graphics& graphics) {
	//dottedLineTest();
	Core::RGB yellow = RGB(255,255,0);
	graphics.SetColor(yellow);

	graphics.DrawString(10,10,"Welcome to");
	drawRainbowText(graphics,10,20,"SpaceWars!");

	graphics.SetColor(yellow);

	float textPad = 5;
	float lineSpacing = 15;
	float currentRow = 100;
	drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,7);	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Controls");					currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,7);	currentRow += lineSpacing;
	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Ship");						currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,3);	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"WASD:  Move and Rotate");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Shift: Brake/Slow Down");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Mouse: Aim/Fire Turret");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"1-5:   Change Turret");		currentRow += lineSpacing;
	//drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,7);	currentRow += lineSpacing;
	currentRow += lineSpacing;
	currentRow += lineSpacing;
	currentRow += lineSpacing;
	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"World");					currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,3);	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Z: (hold) Warp Ship");		currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"X: Set Simple Bounds");		currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"C: Set Complex Bounds");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"P: Pause The Game");	currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,addLeftPad+pad,currentRow,7);	currentRow += lineSpacing;

	graphics.DrawString(500,15,"[MESSAGE BOX IS UNDER DEVELOPMENT]");
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