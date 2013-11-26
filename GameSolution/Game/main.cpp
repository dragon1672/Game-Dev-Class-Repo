#include "Core.h"
#include "Controller.h"
#include "MyRandom.h"

#include "AutoProfileManager.h"

const int SCREEN_WIDTH  = 1500;
const int SCREEN_HEIGHT = 800;
Controller myGame(SCREEN_WIDTH,SCREEN_HEIGHT);

bool update( float dt ) {
	PROFILE("Game Update");
	return myGame.update(dt);
	END_PROFILE;
}
void draw( Core::Graphics& graphics ) {
	PROFILE("Game Draw");
	myGame.draw(graphics);
	END_PROFILE;
}
void startCoreEngine() {
	Core::Init("Space Wars!",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}

#include "Timer.h"
#include <Windows.h>
int main() {
	//* actual game
	START_PROFILING;
	Random::init();
	startCoreEngine();
	LOG_CURRENT_PROFILE;
	STOP_PROFILING;
	//*/
}