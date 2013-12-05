#include "Controller.h"
#include "MyRandom.h"
#include "AutoProfileManager.h"
#include "LogManager.h"
#include "GameMacros.h"

//temp
#include "EndGameView.h"
//end temp

EndGameView Testing;

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
	//temp
	Testing.init(width,height);
	Testing.setScore(8888888);
	//end temp
}
bool Controller::update(float dt) {
	//temp
	Testing.update(dt);
	//end temp
	//myStartScreen.update(dt);
	return false;
}
void Controller::draw(Core::Graphics& graphics) {
	//update graphic pointers
	myGraphic.setGraphic(&graphics);
	//myStartScreen.draw(myGraphic);
	//temp
	Testing.draw(myGraphic);
	//endtemp
}
DynamicPosition *Controller::getMouse() {
	return &mousePos;
}