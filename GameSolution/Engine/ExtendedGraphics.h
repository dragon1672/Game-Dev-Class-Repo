#pragma once
#ifndef EXTENDED_GRAPHICS_H
#define EXTENDED_GRAPHICS_H

#include "Core.h"

class Vector2D;

#define CHAR_SPACING 7//for graphics.drawString()
#define CHAR_HEIGHT 10//for graphics.drawString()

namespace ExtendedGraphics {
	static const int char_spacing = CHAR_SPACING;
	static const int char_height  = CHAR_HEIGHT;
	//drawing manpulations
	void      drawDottedLine (Core::Graphics& graphics, const Vector2D& start, const Vector2D& end, float length);
	void      drawDottedLine (Core::Graphics& graphics, int x1, int y1, int x2, int y2, float length);
	void      drawRainbowText(Core::Graphics& graphics, float x, float y, char* text);
	void      drawPlane( Core::Graphics& graphics, const Vector2D& p1,const Vector2D& p2,const Vector2D& p3,const Vector2D& p4);
	void      drawSquare(Core::Graphics& graphics, const Vector2D& p1,const Vector2D& p2);
	void      textInABox(Core::Graphics& graphics, Core::RGB backCol, Core::RGB textCol, char* text, int x, int y, int width, int height);
	void      drawLoadingBar(Core::Graphics& graphics, const Vector2D& pos, float percent, int width=100, int height=10, Core::RGB boarderColor=RGB(255,255,0), Core::RGB barColor=RGB(255,0,0));
	void      drawLoadingBar(Core::Graphics& graphics, const Vector2D& pos, float current, float max, int width=100, int height=10, Core::RGB boarderColor=RGB(255,255,0), Core::RGB barColor=RGB(255,0,0));
	//color manpulations
	Core::RGB randomColor();
	Core::RGB brightness(Core::RGB col, float percent);
	Core::RGB addR(Core::RGB col, int amount);
	Core::RGB addG(Core::RGB col, int amount);
	Core::RGB addB(Core::RGB col, int amount);
	Core::RGB varyColor( Core::RGB col, int variance);
};

#endif