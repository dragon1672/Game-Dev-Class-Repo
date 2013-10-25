#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"

const Vector2D spaceShipPoints[] = {
								Vector2D(10,12),
								Vector2D(12, 0 ),
								Vector2D( 8,  8 ),
								Vector2D( 0, -20),//tip
								Vector2D(-8,  8 ),
								Vector2D(-12, 0 ),
								Vector2D(-10, 12)
								};
class Spaceship {
private:
	//Shape thisShape(Vector2D, 7, spaceShipPoints[0], spaceShipPoints[1]);//*/
public:
	Vector2D pos;
	Spaceship(int x=0,int y=0) {
		pos = Vector2D(x,y);
	}
	void draw(Core::Graphics graphics);
};



#endif