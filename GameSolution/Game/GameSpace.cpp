#include "GameSpace.h"

GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, Vector2D pos, Core::RGB color) {
	makeGameSpace(color, width, height, pos);
}
void GameSpace::initObjects() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	myShip.init(min.getX()+(width/2),min.getY()+(height/2),this);
	myLerp.init();
	for(int i=0;i<7;i++) {
		myLerp.addPoint(randomWorldPoint());
	}
	/*
	myLerp.addPoint(min);
	myLerp.addPoint(min+Vector2D(0,         (min.getY()+height)/2));
	myLerp.addPoint(min+Vector2D(25,        (min.getY()+height)-100));
	myLerp.addPoint(    Vector2D(.5f*width, (min.getY()+height)));
	myLerp.addPoint(min+Vector2D(width,     height/2));
	myLerp.addPoint(min+Vector2D(width/2,  0));
	//*/
}
void GameSpace::makeGameSpace(Core::RGB color, float width, float height, Vector2D pos) {
	min = pos+Vector2D(0,0);
	max = pos+Vector2D(width,height);
	initObjects();
	Vector2D one   = min;
	Vector2D two   = pos+Vector2D(width,0);
	Vector2D three = max;
	Vector2D four  = pos+Vector2D(0,height);
	toDraw.initialize(color, Matrix3D(), 4, one,two,three,four);
}
void GameSpace::registerBoundary(Boundary *bounds) {
	hasBounds = true;
	boundary = bounds;
}
void GameSpace::draw(Core::Graphics graphics) {
	toDraw.draw(graphics);
	if(hasBounds)
		boundary->draw(graphics);
	myShip.draw(graphics);
	myLerp.draw(graphics);
}
bool GameSpace::update(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	myShip.update(dt);
	myLerp.update(dt);
	return false;
}
Boundary *GameSpace::getBoundary() { return boundary; }
Vector2D GameSpace::getMin() { return min; }
Vector2D GameSpace::getMax() { return max; }
Vector2D GameSpace::collideVector(Vector2D& pos, Vector2D& vel) {
	//if(hasBounds) {
		return boundary->collideVector(pos,vel);
	/*not my job if they don't include a boundary
	} else {
		if(pos.getX() < min.getX() || pos.getX() > max.getX()) return Vector2D(-vel.getX(), vel.getY());
		if(pos.getY() < min.getY() || pos.getY() > max.getY()) return Vector2D( vel.getX(),-vel.getY());
		return vel;
	}//*/
}
//#include <random>
Vector2D GameSpace::randomWorldPoint() {
	//*
	std::random_device rd;//dont like making multiple engines
	std::mt19937 mt(rd()); //seed
	std::uniform_int_distribution<int>distX((int)getMin().getX(),(int)getMax().getX());
	std::uniform_int_distribution<int>distY((int)getMin().getY(),(int)getMax().getY());
	return Vector2D(distX(mt),distY(mt));
	//*/
	//return Vector2D(5,5);
}