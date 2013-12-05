#include "EndGameView.h"
#include "MyGraphics.h"
#include "Font.h"
#include "FontRender.h"
#include "TextFormatting.h"
#include "ParticalTextFormat.h"
#include "DynamicPosRandom.h"
#include <sstream>//for converting 

const char* EndGameView::HEADER_TEXT      = "YOU DIED!!";
const char* EndGameView::SUB_HEADER_TEXT  = "With a Score Of";
const char* EndGameView::FOOTER_TEXT      = "Try to live longer next time";
Core::RGB EndGameView::headerTextColor    =  RGB(255,255,0);
Core::RGB EndGameView::subHeaderTextColor =  RGB(255,255,0);
Core::RGB EndGameView::scoreTextColor     =  RGB(102,255,51);//cool green
Core::RGB EndGameView::footerTextColor    =  RGB(255,255,0);
TextFormatting EndGameView::headerTextStyle   (7,1,headerTextColor,    10);
TextFormatting EndGameView::subHeaderTextStyle(3,1,subHeaderTextColor, 10);
TextFormatting EndGameView::footerTextStyle   (5,1,footerTextColor,    10);

void EndGameView::init(int width, int height) {
	scoreText.reset();
	SCREEN_WIDTH  = width;
	SCREEN_HEIGHT = height;

	Vector2D vertical(0,(float)height);
	Vector2D horzCenter((float)width/2 ,0);
	int headerTextWidth    = headerTextStyle.widthOfString(HEADER_TEXT);
	int subHeaderTextWidth = subHeaderTextStyle.widthOfString(SUB_HEADER_TEXT);
	int footerTextWidth    = footerTextStyle.widthOfString(FOOTER_TEXT);
	int buttonWidth = 200;
	headerTextPos    = .10f * vertical + horzCenter - Vector2D((float)headerTextWidth/2,    0);
	subHeaderTextPos = .25f * vertical + horzCenter - Vector2D((float)subHeaderTextWidth/2, 0);
	footerTextPos    = .60f * vertical + horzCenter - Vector2D((float)footerTextWidth/2,    0);
	Vector2D buttonPos = .75f * vertical + horzCenter - Vector2D((float)buttonWidth/2,      0);

	returnButton.init(&mouse,buttonPos,"Return to main menu",buttonWidth,50);
}
void EndGameView::setScore(int score) {
	Vector2D vertical(0,(float)SCREEN_HEIGHT);
	Vector2D horzCenter((float)SCREEN_WIDTH/2 ,0);
	std::stringstream ss;
	ss << score;

	ParticalTextFormat scoreFormat;
	scoreFormat.init(4,7,scoreTextColor,10);
	scoreFormat.slowEffect = false;
	DynamicPosRandom spawnPoint((float)SCREEN_WIDTH,(float)SCREEN_HEIGHT);
	scoreFormat.spawnLocation = &spawnPoint;

	int scoreTextWidth = scoreFormat.widthOfString(ss.str().c_str());
	scoreTextPos = .35f * vertical + horzCenter - Vector2D((float)scoreTextWidth/2,0);

	scoreText.initText(scoreTextPos,ss.str().c_str(),&Font::defaultFont,&scoreFormat);
};
bool EndGameView::update(float dt) {
	scoreText.update(dt);
	return returnButton.isPressed();
}
void EndGameView::draw(MyGraphics& graphics) {
	returnButton.draw(graphics);
	scoreText.draw(graphics);
	FontRender::draw(graphics, headerTextPos,    &Font::defaultFont, &headerTextStyle,    HEADER_TEXT);
	FontRender::draw(graphics, subHeaderTextPos, &Font::defaultFont, &subHeaderTextStyle, SUB_HEADER_TEXT);
	FontRender::draw(graphics, footerTextPos,    &Font::defaultFont, &footerTextStyle,    FOOTER_TEXT);
}