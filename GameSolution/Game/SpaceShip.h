#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "Vector 2.h"
#include "Core.h"


class Spaceship {
public:
	Vector2D pos;
	Spaceship(int x=0,int y=0) {
		pos = Vector2D(x,y);
	}
	void draw(Core::Graphics graphics);
	void addWorld(int x, int y);
};



#endif