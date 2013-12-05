#include "Controller.h"
#include "MyRandom.h"
#include "AutoProfileManager.h"
#include "LogManager.h"
#include "GameMacros.h"


Controller::Controller (int width, int height) : width(width), 
												 height(height),
												 myGameView(width,height) {
	LOG(Info,"Controller Init Start",0);
	const char* options[] = {
		"Start Game",
		"Help",
		"Exit"
	};
	myStartScreen.init(width,height,options,SIZE_OF_ARRAY(options));
}
bool Controller::update(float dt) {
	myStartScreen.update(dt);
	return false;
}
void Controller::draw(Core::Graphics& graphics) {
	//update graphic pointers
	myGraphic.setGraphic(&graphics);
	myStartScreen.draw(myGraphic);
}
DynamicPosition *Controller::getMouse() {
	return &mousePos;
}