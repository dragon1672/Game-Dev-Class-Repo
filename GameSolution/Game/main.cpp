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
	//*debugging
	START_PROFILING;
	//doing look with manual timers
	for(int i=0;i<10;i++) {
		Timer myTimer;
		myTimer.start();
		Sleep(100);
		{
			Timer myTimer;
			myTimer.start();
			Sleep(100);
			AutoProfileManager::addEntry("Testing2",myTimer.getCurrentTime()*1000);
		}
		AutoProfileManager::addEntry("Testing",myTimer.getCurrentTime()*1000);

	}
	//same for loop
	for(int i=0;i<10;i++) {
		PROFILE("_AUTO_TESTING");
		Sleep(100);
		PROFILE("_AUTO_TESTING_2");
		Sleep(100);
		END_PROFILE;
		END_PROFILE;

	}
	//finished
	LOG_CURRENT_PROFILE;
	STOP_PROFILING;
	return 0;
	//*/

	/* actual game
	START_PROFILING;
	Random::init();
	startCoreEngine();
	LOG_CURRENT_PROFILE;
	STOP_PROFILING;
	//*/
}