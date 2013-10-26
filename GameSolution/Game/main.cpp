#include "Engine.h"
#include "Core.h"
#include "SpaceShip.h"
#include "Controller.h"
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

Controller myProject(SCREEN_WIDTH,SCREEN_WIDTH);
bool update( float dt ) {
	return myProject.update(dt);
	//if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE )) return true;
	//return false;
}
void draw( Core::Graphics& graphics ) {
	myProject.draw(graphics);
}

void startCoreEngine() {
	Core::Init("Space Quest",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}

int main() {
	startCoreEngine();
}

