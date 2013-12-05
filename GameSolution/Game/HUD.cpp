#include "HUD.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"
#include "PlayerControls.h"
#include "LogManager.h"
#include "Font.h"
#include "FontRender.h"
#include "ScoreManager.h"
#include <sstream>

Core::RGB HUD::defaultTextColor = RGB(255,255,0);
TextFormatting HUD::titleStyle(4,1,defaultTextColor,10);
TextFormatting ticker_style;
const char* HUD::ticker_preText = "Score: ";


HUD::HUD(int screenWidth, int screenHeight, ScoreManager * scoreBoard) : screenWith(screenWith), screenHeight(screenHeight),scoreBoard(scoreBoard) {
	LOG(Info,"Init HUD",0);
	pad = 20;
	addLeftPad  = 200-pad;
	addRightPad = 0;
	addTopPad   = 100-pad;
	addBotPad   = 0;
	worldWidth  = screenWidth  - addRightPad - addLeftPad - 2 * pad;
	worldHeight = screenHeight - addTopPad   - addBotPad  - 2 * pad;
	//ticker
	ticker_pos      = Vector2D(addLeftPad,0);
	ticker_width    = worldWidth;
	ticker_height   = addTopPad+pad;
	ticker_percent  = 1;
	ticker_speed    = .25f;
	ticker_textPad  = 20;
	int particalSize = (ticker_height-2*ticker_textPad) / Letter::LETTER_HEIGHT;
	ticker_style.init(particalSize,1,defaultTextColor,10);
	ticker_graphics.init(ticker_pos,ticker_width,ticker_height);
}

int HUD::getTickerTextWidth() {
	std::stringstream ss;
	ss << ticker_preText << scoreBoard->getTotalPoints();
	return ticker_style.widthOfString(ss.str().c_str());
}
void      HUD::draw(MyGraphics& graphics) {
	ticker_graphics.setGraphic(&graphics);
	//ticker
	std::stringstream ss;
	ss << ticker_preText << scoreBoard->getTotalPoints();
	FontRender::draw(ticker_graphics,ticker_pos+Vector2D(ticker_width*ticker_percent,ticker_textPad),&Font::defaultFont,&ticker_style,ss.str().c_str());

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

	//graphics.setColor(RGB(100,100,100));
}
void      HUD::update(float dt) {
	ticker_percent += ticker_speed * dt;
	if(ticker_percent>1) {
		ticker_percent = -getTickerTextWidth()/ticker_width;
	}
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