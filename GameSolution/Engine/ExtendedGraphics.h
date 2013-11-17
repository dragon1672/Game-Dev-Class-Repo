#pragma once
#ifndef EXTENDED_GRAPHICS_H
#define EXTENDED_GRAPHICS_H

#include "Core.h"

class Vector2D;

#define CHAR_SPACING 7//for graphics.drawString()

namespace ExtendedGraphics {
	Core::RGB randomColor();
	void      drawDottedLine (Core::Graphics& graphics, const Vector2D& start, const Vector2D& end, float length);
	void      drawDottedLine (Core::Graphics& graphics, int x1, int y1, int x2, int y2, float length);
	void      drawRainbowText(Core::Graphics& graphics, float x, float y, char* text);
};

#endif