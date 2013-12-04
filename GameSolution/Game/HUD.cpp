#include "HUD.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"
#include "PlayerControls.h"
#include "LogManager.h"

#include "Timer.h"//Only used for loading bar with the under development section
Timer loadingBarTimer;//started in constructor
float loadingBarPercent = 0;//updated in draw


using ExtendedGraphics::drawDottedLine;
using ExtendedGraphics::drawRainbowText;
using ExtendedGraphics::drawPlane;
using ExtendedGraphics::drawSquare;

Core::RGB HUD::defaultTextColor = RGB(255,255,0);

HUD::HUD(int screenWidth, int screenHeight) : screenWith(screenWith), screenHeight(screenHeight) {
	LOG(Info,"Init HUD",0);
	pad = 20;
	addLeftPad  = 200-pad;
	addRightPad = 0;
	addTopPad   = 100-pad;
	addBotPad   = 0;
	worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
	worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
	loadingBarTimer.start();
}


void      HUD::draw(MyGraphics& graphics) {
	graphics.setColor(defaultTextColor);
	graphics.drawString(10,10,"Welcome to");
	graphics.drawRainbowText(10,20,"SpaceWars!");
	graphics.setColor(defaultTextColor);

	int textPad = 5;
	int lineSpacing = 15;
	int currentRow = 100;
	int length = (int)(addLeftPad+pad);

	float mainDash  = 6;
	float subDash   = 4;
	float smallDash = 1;

	graphics.drawDottedLine(0,currentRow,length,currentRow,mainDash);	currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"Controls");					currentRow += lineSpacing;
	graphics.drawDottedLine(0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	
	//extra line
	currentRow += lineSpacing;
	
	graphics.drawString(textPad,currentRow,"Ship");						currentRow += lineSpacing;
	graphics.drawDottedLine(0,currentRow,length,currentRow,smallDash);	currentRow += lineSpacing;

	graphics.drawString(textPad,currentRow,"WASD:  Move and Rotate");	currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"Shift: Brake/Slow Down");	currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"Mouse: Aim Turret");		currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"1-5:   Change Turret");		currentRow += lineSpacing;
	graphics.drawDottedLine(0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	
	//adding extra lines
	currentRow += 4*lineSpacing;

	graphics.drawDottedLine(0,currentRow,length,currentRow,subDash);	currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"World");					currentRow += lineSpacing;
	graphics.drawDottedLine(0,currentRow,length,currentRow,smallDash);	currentRow += lineSpacing;

	graphics.drawString(textPad,currentRow,"Z: (hold) Warp Ship");		currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"X: Set Simple Bounds");		currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"C: Set Complex Bounds");	currentRow += lineSpacing;
	graphics.drawString(textPad,currentRow,"P: Pause The Game");		currentRow += lineSpacing;
	graphics.drawDottedLine(0,currentRow,length,currentRow,mainDash);	currentRow += lineSpacing;

	//under development
	loadingBarPercent+=(loadingBarPercent>1)? -1 : loadingBarTimer.interval()/2;
	graphics.drawLoadingBar(Vector2D(500,30),loadingBarPercent,250,20);
	graphics.drawLoadingBar(Vector2D(500,60),loadingBarPercent,50,5);
	graphics.drawString(500,15,"[MESSAGE BOX IS UNDER DEVELOPMENT]");
	graphics.setColor(RGB(100,100,100));
}
void HUD::paintWorld(MyGraphics& graphics, Core::RGB color) {
	graphics.setColor(color);
	graphics.drawSquare(getWorldoffset(),getWorldoffset() + Vector2D(getWorldWidth(),getWorldHeight()) );
}
void HUD::worldPopup(MyGraphics& graphics, char* text, Core::RGB color, int width, int height) {
	Vector2D popupOffset = getWorldoffset() + Vector2D((getWorldWidth() - width)/2,(getWorldHeight() - height)/2);
	graphics.textInABox(color,defaultTextColor,text,(int)popupOffset.getX(),(int)popupOffset.getY(),(int)width,(int)height);
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