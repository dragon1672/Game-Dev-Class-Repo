#include "Engine.h"
#include "Core.h"
#include "SpaceShip.h"
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

Spaceship testing(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+50);

bool update( float dt ) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE )) return true;
	return false;
}
void draw( Core::Graphics& graphics ) {
	graphics.SetColor(RGB(255,255,0));
	graphics.DrawString(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-20,"Hello World");
	//graphics.DrawLine(10,10,400,300);
	testing.draw(graphics);
}

void startCoreEngine() {
	Core::Init("Testing",SCREEN_WIDTH,SCREEN_HEIGHT );
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}
int main() {
	startCoreEngine();
}

