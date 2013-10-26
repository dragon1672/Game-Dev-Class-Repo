#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
#include <time.h>
//change acc to mesure difference in time no update each frame
class Spaceship {
private:
	static Shape thisShape;
	Vector2D acc;
	static const float brakePower;
public:
	Vector2D pos;
	Spaceship(float x=0,float y=0) {
		pos = Vector2D(x,y);
	}
	void draw(Core::Graphics graphics);
	void addAcc(Vector2D toAdd,float scalar=1);
	void update(float dt);
	void brake(float scalar=1);
	void changePos(Vector2D newLocation);
};



#endif