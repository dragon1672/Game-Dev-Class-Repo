#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "MyGraphics.h"
#include "Vector 2.h"
#include "Core.h"
#include "DynamicPosition.h"

class Button {
	static Core::RGB DEFAULT_hoverColor;
	static Core::RGB DEFAULT_defaultColor;
	Core::RGB hoverColor;
	Core::RGB defaultColor;

	DynamicPosition * cursor;

	Vector2D pos;
	int width, height;
	const char* text;
	void init(DynamicPosition * cursor, Vector2D& pos, const char* text, int width, int height, Core::RGB setHoverColor = DEFAULT_hoverColor, Core::RGB setDefaultColor = DEFAULT_defaultColor);
	void update(float dt);
	void draw(MyGraphics& graphics);
	bool mouseWithinBounds();
	bool isPressed();
	Core::RGB currentColor();
};

#endif