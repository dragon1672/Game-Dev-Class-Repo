#include "Core.h"
#include "SpaceShip.h"
#include "GameSpace.h"
#include "Controller.h"
#include "MyRandom.h"

//-----------/* Rename "Constroller" to "Controller" */-----------/
const int SCREEN_WIDTH  = 1500;
const int SCREEN_HEIGHT = 800;
Controller myGame(SCREEN_WIDTH,SCREEN_HEIGHT);

bool update( float dt ) {
	return myGame.update(dt);
}
void draw( Core::Graphics& graphics ) {
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
	startCoreEngine();
}

