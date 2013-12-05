#pragma once
#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Vector 2.h"
#include "Core.h"
#include "Font.h"
#include "TextParticalManager.h"
#include "ParticalTextFormat.h"

#include "MyGraphics.h"

class StartScreen {
public:
	static const int WINDOW_STILL_ACTIVE = -1;//relates to status code
	int statusCode;
	static const char* TITLE_TEXT;
	static Core::RGB   TITLE_COLOR;
	static const char* SUBTITLE_TEXT;
	static Core::RGB   SUBTITLE_COLOR;
	
private:
	Font myFont;
	TextParticalManager textManager;
	ParticalTextFormat titleFormat;
	ParticalTextFormat subTitleFormat;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
public:
	void init(int screenWidth, int screenHeight);
	void update(float dt);//since it will have buttons
	void draw(MyGraphics& graphics);
};

#endif