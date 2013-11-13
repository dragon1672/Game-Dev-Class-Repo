#include "Core.h"
#include "SpaceShip.h"
#include "GameSpace.h"
#include "Controller.h"
#include "MyRandom.h"

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
	Core::Init("Space Quest",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}
int main() {
	Random::init();
	startCoreEngine();
}

