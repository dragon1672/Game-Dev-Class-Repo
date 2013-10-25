#include <stdarg.h>
#include "Vector 2.h"
#include "Core.h"
class Shape {
private:
	Vector2D *points;
	int count;
	int maxX;
	int maxY;
	int minX;
	int minY;
	void calcMinAndMax();
public:
	Shape(int count,...);
	void draw(Core::Graphics graphics, Vector2D transpose=Vector2D(0,0), int scale=1);
};