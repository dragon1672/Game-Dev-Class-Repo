#pragma once


#include <stdarg.h>
#include "Vector 2.h"
#include "Core.h"
class Shape {
protected:
	void destory();
	Vector2D *points;
	int count;
private:
	bool constructed;
	float maxX;
	float maxY;
	float minX;
	float minY;
	Core::RGB myColor;
	void calcMinAndMax();
public:
	Shape();
	Shape(Core::RGB color, int count,...);
	~Shape();
	bool initialize(Core::RGB, int count,...);
	bool initialize(Core::RGB, int count, va_list toStore);
	bool initialize(Core::RGB, int count, Vector2D *toAdd);
	void draw(Core::Graphics graphics, Vector2D transpose=Vector2D(0,0),   float scale=1);
	bool simpleOutOfBounds(Vector2D pos, Vector2D transpose=Vector2D(0,0), float scale=1);
	void setRandomColor();
	void setColor(Core::RGB toSet);
	bool isConstructed();
	float getMinX();
	float getMinY();
	float getMaxX();
	float getMaxY();
};
