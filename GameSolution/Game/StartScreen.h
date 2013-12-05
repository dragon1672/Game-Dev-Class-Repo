#pragma once
#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Vector 2.h"
#include "Core.h"
#include "Font.h"
#include "TextParticalManager.h"
#include "ParticalTextFormat.h"
#include "Button.h"
#include "TargetMouse.h"

#include "MyGraphics.h"

class StartScreen {
public:
	static const int WINDOW_STILL_ACTIVE = -1;//relates to status code

	static const int MAX_BUTTONS = 5;

	static const char* TITLE_TEXT;
	static Core::RGB   TITLE_COLOR;
	static const char* SUBTITLE_TEXT;
	static Core::RGB   SUBTITLE_COLOR;
	
private:
	Font myFont;
	TextParticalManager textManager;
	ParticalTextFormat titleFormat;
	ParticalTextFormat subTitleFormat;
	TargetMouse cursor; 
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Button options[MAX_BUTTONS];
	int numOfButtons;
	//functions
	void initTitleText();
	void initButtons(const char* optionText[], int numOfOptions);
public:
	void init(int screenWidth, int screenHeight, const char* optionText[], int numOfOptions);
	int  update(float dt);//since it will have buttons
	void draw(MyGraphics& graphics);
};

#endif