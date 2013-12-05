#pragma once
#ifndef FONT_RENDER_H
#define FONT_RENDER_H

#include "Vector 2.h"

class MyGraphics;
class TextFormatting;
class Font;

class FontRender {
public:
	void draw(MyGraphics& graphics, Vector2D& pos, Font *myFont, TextFormatting * format, const char* text);
};

#endif