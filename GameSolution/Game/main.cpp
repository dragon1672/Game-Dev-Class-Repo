#include "Core.h"
#include "Controller.h"
#include "MyRandom.h"
#include "LogManager.h"
#include "DebugTimer.h"
#include "AutoProfileManager.h"

//temp
#include "TextParticalManager.h"
Font myTestingFont;
TextParticalManager myTestingTextManager;


const int SCREEN_WIDTH  = 1500;
const int SCREEN_HEIGHT = 800;
Controller myGame(SCREEN_WIDTH,SCREEN_HEIGHT);

bool update( float dt ) {
	//TESTING-------------------------------------------------------------------
	myTestingTextManager.update(dt);
	PROFILE("Game Update");
	return myGame.update(dt);
	END_PROFILE;
}
void draw( Core::Graphics& graphics ) {
	PROFILE("Game Draw");
	myGame.draw(graphics);
	END_PROFILE;
	//TESTING-------------------------------------------------------------------
	myTestingTextManager.draw(graphics);
}
void startCoreEngine() {
	LOG(Info,"Begin Load Resources",0);
	Core::Init("Space Wars!",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}

int main() {
	//TEMP
	myTestingFont.init("../FONT.TXT");
	Vector2D testTextPos(500,500);
	myTestingTextManager.initText(testTextPos,"[#Sam's Text. 1+1=2, yus!]",&myTestingFont,3,2);

	LOG(Info,"Program Start",0);
	//* actual game
	START_PROFILING;
	Random::init();
	START_GLOBAL_TIMER;
	startCoreEngine();
	LOG_CURRENT_PROFILE;
	STOP_PROFILING;
	END_LOG
	//*/
}