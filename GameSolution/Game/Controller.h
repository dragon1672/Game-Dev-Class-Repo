#ifndef CONTROLLER
#define CONTROLLER

#include "SpaceShip.h"
#include "Core.h"
#include "Engine.h"
class Controller {
private:
	static Vector2D accX;
	static Vector2D accY;
	int width;
	int height;
	Spaceship player;
	Shape world;
public:
	Controller(int width, int height);
	void loadAssets();
	bool update(float dt);
	void draw( Core::Graphics graphics );
};
#endif