#include "Core.h"
#include "SpaceShip.h"
#include "GameSpace.h"
#include "Controller.h"
#include "MyRandom.h"
#include "ParticalEffect.h"

//-----------/* Rename "Constroller" to "Controller" */-----------/
const int SCREEN_WIDTH  = 1500;
const int SCREEN_HEIGHT = 800;
Controller myGame(SCREEN_WIDTH,SCREEN_HEIGHT);
ParticalEffect potato;


bool update( float dt ) {
	potato.update(dt);
	return myGame.update(dt);
}
void draw( Core::Graphics& graphics ) {
	potato.draw(graphics);
	myGame.draw(graphics);
}
void startCoreEngine() {
	Core::Init("Space Wars!",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}
int main() {
	Random::init();
	potato.init(1000,Vector2D(500,500),1.5);
	startCoreEngine();
}


/*PLANNED TODO
-refactor to basic game entitiy object (pos, vel)
	update Controller to just look through entities
		this process of adding entities will be similiar to adding turrets on my ship
	collision edits game entity?
-refactor bullet manager to only hold array of points
	require turrets to create the array of bullets
	make bullet an abstract class
	implement a tracking bullet

//*/