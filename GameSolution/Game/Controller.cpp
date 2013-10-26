#include "Controller.h"
Vector2D Controller::accX(1, 0);
Vector2D Controller::accY(0, 1);
#define PAD 10
#define TASKBAR_HEIGHT 170

Controller::Controller(int width, int height) {
	this->width  = width;
	this->height = height;
	loadAssets();
}
void Controller::loadAssets() {
	player = Spaceship(width/2.0f,height/2.0f);
	float topPad = 30;
	float worldHeight = height - topPad;
	world  = Shape(4,Vector2D(PAD,topPad), Vector2D(width-PAD,topPad), Vector2D(width-PAD,worldHeight-PAD-TASKBAR_HEIGHT), Vector2D(PAD,worldHeight-PAD-TASKBAR_HEIGHT) );
}
bool Controller::update(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	if(Core::Input::IsPressed( Core::Input::KEY_UP       )) player.addAcc(-accY);
	if(Core::Input::IsPressed( Core::Input::KEY_DOWN     )) player.addAcc( accY);
	if(Core::Input::IsPressed( Core::Input::KEY_LEFT     )) player.addAcc(-accX);
	if(Core::Input::IsPressed( Core::Input::KEY_RIGHT    )) player.addAcc( accX);
	if(Core::Input::IsPressed( Core::Input::BUTTON_SHIFT )) player.brake ();
	player.update(dt);
	return false;
}
void Controller::draw( Core::Graphics graphics ) {
	graphics.SetColor(RGB(255,255,0));
	graphics.DrawString(10,10,"Space Quest");
	world.draw(graphics);
	player.draw(graphics);
}