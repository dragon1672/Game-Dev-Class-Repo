#pragma once
#ifndef END_GAME_VIEW_H
#define END_GAME_VIEW_H

#include "View.h"
#include "Button.h"
#include "TextParticalManager.h"
#include "Core.h"
#include "TargetMouse.h"

class EndGameView : View {
private:
	static const char* HEADER_TEXT;
	static const char* SUB_HEADER_TEXT;
	static const char* FOOTER_TEXT;
	//style
	static TextFormatting headerTextStyle;
	static TextFormatting subHeaderTextStyle;
	static TextFormatting footerTextStyle;
	//color
	static Core::RGB headerTextColor;
	static Core::RGB subHeaderTextColor;
	static Core::RGB scoreTextColor;
	static Core::RGB footerTextColor;
	//pos
	Vector2D headerTextPos;
	Vector2D subHeaderTextPos;
	Vector2D scoreTextPos;
	Vector2D footerTextPos;
	TargetMouse mouse;

	int score;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Button returnButton;
	TextParticalManager scoreText;
public:
	void init(int width, int height);
	void setScore(int score);
	bool update(float dt);
	void draw(MyGraphics& graphics);
};

#endif