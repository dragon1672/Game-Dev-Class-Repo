#pragma once
#ifndef BOXED_OFF_GRAPHIC_H
#define BOXED_OFF_GRAPHIC_H

#include "MyGraphics.h"
#include "Vector 2.h"

class BoxedOffGraphic : public MyGraphics {
private:
	Vector2D pos;
	float width,height;
	bool isInBox(Vector2D& pos2Check,Vector2D&boxLocation,int width, int height);
public:
	void init(const Vector2D& pos, float width, float height);
	void drawLine(Vector2D p1, Vector2D p2);
};

#endif