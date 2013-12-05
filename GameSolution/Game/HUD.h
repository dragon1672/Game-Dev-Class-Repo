#pragma once
#include "Core.h"
#include "Vector 2.h"
#include "MyGraphics.h"
#include "BoxedOffGraphic.h"//for ticking message Box

#include "TextFormatting.h"

class ScoreManager;

class HUD {
	static TextFormatting titleStyle;
	int   screenWith;
	int   screenHeight;
	float pad;
	float addLeftPad;
	float addRightPad;
	float addTopPad;
	float addBotPad;
	float worldWidth;
	float worldHeight;

	ScoreManager * scoreBoard;

	//ticking box
	Vector2D ticker_pos;
	float    ticker_width;
	float    ticker_height;
	float    ticker_percent;
	float    ticker_speed;
	float    ticker_textPad;
	TextFormatting  ticker_style;
	BoxedOffGraphic ticker_graphics;

	static const char* ticker_preText;

	int getTickerTextWidth();
public:
	static Core::RGB defaultTextColor;
	HUD(int screenWidth, int screenHeight, ScoreManager * scoreBoard);
	void     draw(MyGraphics& graphics);
	void     update(float dt);
	Vector2D getWorldoffset();
	float    getWorldWidth();
	float    getWorldHeight();
	void HUD::paintWorld(MyGraphics& graphics, Core::RGB color);
	void HUD::worldPopup(MyGraphics& graphics, char* text,Core::RGB color, int width=500, int height=100);
};