#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "Vector 2.h"
#include "Core.h"


class Spaceship {
private:
	Vector2D pos;
public:
	Spaceship(int x=0,int y=0) {
		pos = Vector2D(x,y);
	}
	void draw(Core::Graphics graphics);
};



#endif