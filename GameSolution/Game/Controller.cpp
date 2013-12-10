#include "Controller.h"
#include "MyRandom.h"
#include "AutoProfileManager.h"
#include "LogManager.h"
#include "GameMacros.h"

#include "DebugMemHeader.h"
#include <sstream>

const char* Controller::startScreenOptions[] = {
													"Start Game",
													"Exit"
												};

Controller::Controller (int width, int height) : width(width), 
												 height(height),
												 myGameView(width,height) {
	LOG(Info,"Controller Init Start",0);
	myStartScreen.init(width,height,startScreenOptions,SIZE_OF_ARRAY(startScreenOptions));
	activeInterface = StartScreen::WINDOW_STILL_ACTIVE;
	interfaces[0] = &myGameView;
}
void drawDebug(MyGraphics& graphics) 
{
	graphics;
#ifdef _DEBUG
	static unsigned int trackedHighWaterCount = 0;
	_CrtMemState memCheckPoint;
	_CrtMemCheckpoint(&memCheckPoint);

	trackedHighWaterCount = (trackedHighWaterCount<memCheckPoint.lSizes[_CLIENT_BLOCK])? memCheckPoint.lSizes[_CLIENT_BLOCK] : trackedHighWaterCount;

	graphics.setColor(RGB(235,176,53));
	graphics.setBackgroundColor(RGB(235,176,53));
	graphics.drawSquare(Vector2D(0,0),Vector2D(200,75));

	graphics.setColor(RGB(33,133,89));
	std::stringstream ss;
	ss <<  "lCounts: "          << memCheckPoint.lCounts[_CLIENT_BLOCK] << "\n"
		<< "lSizes: "           << memCheckPoint.lSizes[_CLIENT_BLOCK]  << "\n"
		<< "Highwater: "        << memCheckPoint.lHighWaterCount        << "\n"
		<< "CustomHighWater: "  << trackedHighWaterCount;
	graphics.drawString(5,5,ss.str().c_str());
	graphics.setBackgroundColor(RGB(0,0,0));
#endif
}
bool Controller::update(float dt) {
	if(activeInterface == StartScreen::WINDOW_STILL_ACTIVE) {
		activeInterface = myStartScreen.update(dt);
	} else {
		if(interfaces[activeInterface]->update(dt)) {
			activeInterface = StartScreen::WINDOW_STILL_ACTIVE;
		}
	}
	if(activeInterface == SIZE_OF_ARRAY(startScreenOptions)-1
		|| Core::Input::IsPressed( Core::Input::KEY_ESCAPE)) {
		return true;//exit the game
	}
	return false;
}
void Controller::draw(Core::Graphics& graphics) {
	//update graphic pointers
	myGraphic.setGraphic(&graphics);

	if(activeInterface == StartScreen::WINDOW_STILL_ACTIVE
		|| activeInterface == SIZE_OF_ARRAY(startScreenOptions)-1) {
		myStartScreen.draw(myGraphic);
	} else {
		interfaces[activeInterface]->draw(myGraphic);
	}
#ifdef _DEBUG
	drawDebug(myGraphic);
#endif
}
DynamicPosition *Controller::getMouse() {
	return &mousePos;
}