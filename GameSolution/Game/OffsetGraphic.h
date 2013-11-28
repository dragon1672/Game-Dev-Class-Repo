#pragma once
#ifndef Offset_Graphic_H
#define Offset_Graphic_H

#include "MyGraphics.h"
#include "Vector 2.h"

class OffsetGraphic : public MyGraphics {
private:
	Vector2D transpose;
	float width,height;
public:
	void init(const Vector2D& offset, float width, float height);
	void drawLine(Vector2D p1, Vector2D p2);
};

#endif