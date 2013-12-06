#include "Core.h"
#include "Controller.h"
#include "MyRandom.h"
#include "LogManager.h"
#include "DebugTimer.h"
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
	LOG(Info,"Begin Load Resources",0);
	Core::Init("Space Wars!",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}

void logTest() {
	LOG(Info,"---------------------------------LOGGING FUNCTION TEST---------------------------------",0);
	LOG_SEVERITY(0);

	LOG(Info,"---Should display [level] test 1 level:0",0);

	LOG(Info,"Info Test 1 level:0",0);
	LOG(Info,"Info Test 1 level:1",1);
	LOG(Warning,"Warning Test 1 level:0",0);
	LOG(Warning,"Warning Test 1 level:1",1);
	LOG(Error,"Error Test 1 level:0",0);
	LOG(Error,"Error Test 1 level:1",1);
	LOG(Severe,"Severe Test 1 level:0",0);
	LOG(Severe,"Severe Test 1 level:1",1);

	LOG_SEVERITY(2);
	
	LOG(Info,"---Should display [level] test 1 level:(0 and 1)",0);

	LOG(Info,"Info Test 2 level:0",0);
	LOG(Info,"Info Test 2 level:1",1);
	LOG(Warning,"Warning Test 2 level:0",0);
	LOG(Warning,"Warning Test 2 level:1",1);
	LOG(Error,"Error Test 2 level:0",0);
	LOG(Error,"Error Test 2 level:1",1);
	LOG(Severe,"Severe Test 2 level:0",0);
	LOG(Severe,"Severe Test 2 level:1",1);

	LOG_SEVERITY(0);

	LOG(Info,"----------------------------------------END TEST----------------------------------------",0);
}

int main() {
	logTest();
	//ASSERT(false,"testing");


	LOG(Info,"Program Start",0);
	//* actual game
	START_PROFILING;
	Random::init();
	START_GLOBAL_TIMER;
	startCoreEngine();

	LOG(Info,"Program Has Ended",0);

	LOG_CURRENT_PROFILE;
	STOP_PROFILING;
	END_LOG;
	//*/
	return 0;
}