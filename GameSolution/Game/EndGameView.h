#pragma once
#ifndef END_GAME_VIEW_H
#define END_GAME_VIEW_H

#include "View.h"
#include "Button.h"

class EndGameView : View {
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Button returnButton;
public:
	void init(int width, int height);
	bool update(float dt);
	void draw(Core::Graphics& graphics);
};

#endif