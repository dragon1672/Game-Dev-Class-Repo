#include "Engine.h"
#include "SpaceShip.h"

const float Spaceship::brakePower = 2;
const Vector2D shipPoints[] = {
								Vector2D(10,12),
								Vector2D(12, 0 ),
								Vector2D( 8,  8 ),
								Vector2D( 0, -20),//tip
								Vector2D(-8,  8 ),
								Vector2D(-12, 0 ),
								Vector2D(-10, 12)
							  };

Shape Spaceship::thisShape( sizeof(shipPoints)/sizeof(shipPoints[0]),
							shipPoints[0],
							shipPoints[1],
							shipPoints[2],
							shipPoints[3],
							shipPoints[4],
							shipPoints[5],
							shipPoints[6]
						 );
void Spaceship::changePos(Vector2D newLocation) {
	pos = newLocation;
}
void Spaceship::draw(Core::Graphics graphics) {
	graphics.SetColor(RGB(0,255,0));
	thisShape.draw(graphics,pos);
	/*
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
	//*/
}
void Spaceship::addAcc(Vector2D toAdd, float scalar) {
	acc = acc+(scalar*toAdd);
}
void Spaceship::brake(float scalar) {
	float newX = 0;
	float brakePower = scalar*(this->brakePower);
	float current = acc.getX();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newX = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	float newY = 0;
	current = acc.getY();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newY = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	acc = Vector2D(newX,newY);
}
void Spaceship::update(float dt) {
	pos = pos+(dt*acc);
}