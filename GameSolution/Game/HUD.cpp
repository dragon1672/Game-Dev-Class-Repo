#include "HUD.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"
#include "PlayerControls.h"

#include "Timer.h"//Only used for loading bar with the under development section
Timer loadingBarTimer;//started in constructor
float loadingBarPercent = 0;//updated in draw


using ExtendedGraphics::drawDottedLine;
using ExtendedGraphics::drawRainbowText;
using ExtendedGraphics::drawPlane;
using ExtendedGraphics::drawSquare;

Core::RGB HUD::defaultTextColor = RGB(255,255,0);

HUD::HUD(int screenWidth, int screenHeight) : screenWith(screenWith), screenHeight(screenHeight) {
	pad = 20;
	addLeftPad  = 200-pad;
	addRightPad = 0;
	addTopPad   = 100-pad;
	addBotPad   = 0;
	worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
	worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
	loadingBarTimer.start();
}


void      HUD::draw(Core::Graphics& graphics) {
	graphics.SetColor(defaultTextColor);
	graphics.DrawString(10,10,"Welcome to");
	drawRainbowText(graphics,10,20,"SpaceWars!");
	graphics.SetColor(defaultTextColor);

	int textPad = 5;
	int lineSpacing = 15;
	int currentRow = 100;
	int length = (int)(addLeftPad+pad);

	float mainDash  = 6;
	float subDash   = 4;
	float smallDash = 1;

	drawDottedLine(graphics,0,currentRow,length,currentRow,mainDash);	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Controls");					currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	
	//extra line
	currentRow += lineSpacing;
	
	graphics.DrawString(textPad,currentRow,"Ship");						currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,length,currentRow,smallDash);	currentRow += lineSpacing;

	graphics.DrawString(textPad,currentRow,"WASD:  Move and Rotate");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Shift: Brake/Slow Down");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"Mouse: Aim Turret");		currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"1-5:   Change Turret");		currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	
	//adding extra lines
	currentRow += 4*lineSpacing;

	drawDottedLine(graphics,0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"World");					currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,length,currentRow,smallDash);	currentRow += lineSpacing;

	graphics.DrawString(textPad,currentRow,"Z: (hold) Warp Ship");		currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"X: Set Simple Bounds");		currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"C: Set Complex Bounds");	currentRow += lineSpacing;
	graphics.DrawString(textPad,currentRow,"P: Pause The Game");		currentRow += lineSpacing;
	drawDottedLine(graphics,0,currentRow,length,currentRow,mainDash);	currentRow += lineSpacing;

	//under development
	loadingBarPercent+=(loadingBarPercent>1)? -1 : loadingBarTimer.interval()/2;
	ExtendedGraphics::drawLoadingBar(graphics,Vector2D(500,30),loadingBarPercent,250,20);
	graphics.DrawString(500,15,"[MESSAGE BOX IS UNDER DEVELOPMENT]");
	graphics.SetColor(RGB(100,100,100));
}
void HUD::paintWorld(Core::Graphics graphics, Core::RGB color) {
	graphics.SetColor(color);
	drawSquare(graphics, getWorldoffset(),getWorldoffset() + Vector2D(getWorldWidth(),getWorldHeight()) );
}
void HUD::worldPopup(Core::Graphics graphics, char* text, Core::RGB color, int width, int height) {
	Vector2D popupOffset = getWorldoffset() + Vector2D((getWorldWidth() - width)/2,(getWorldHeight() - height)/2);
	ExtendedGraphics::textInABox(graphics,color,defaultTextColor,text,(int)popupOffset.getX(),(int)popupOffset.getY(),(int)width,(int)height);
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