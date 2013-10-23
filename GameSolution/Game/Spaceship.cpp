#include "Engine.h"
#include "SpaceShip.h"

void Spaceship::draw(Core::Graphics graphics) {
	int x = pos.getX();
	int y = pos.getY();
	graphics.SetColor(RGB(0,255,0));
	graphics.DrawLine(x,    y-20, x-8,  y+8); //front left
	graphics.DrawLine(x,    y-20, x+8,  y+8); //front right
	
	graphics.SetColor(RGB(255,128,0));
	graphics.DrawLine(x-8,  y+8,  x-10, y);   //shooter left
	graphics.DrawLine(x+8,  y+8,  x+10, y);   //shooter right
	
	graphics.SetColor(RGB(255,0,0));
	graphics.DrawLine(x-12, y,    x-10, y+12);//back left
	graphics.DrawLine(x+12, y,    x+10, y+12);//back right
	graphics.DrawLine(x-10, y+12, x+10, y+12);//butt
}