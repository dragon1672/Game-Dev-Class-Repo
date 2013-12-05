#include "Controller.h"
#include "MyRandom.h"
#include "AutoProfileManager.h"
#include "LogManager.h"
#include "GameMacros.h"

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
}
DynamicPosition *Controller::getMouse() {
	return &mousePos;
}