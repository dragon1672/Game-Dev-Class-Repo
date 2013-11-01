#include "GameSpace.h"

GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, Vector2D pos, Core::RGB color) {
	makeGameSpace(color, width, height, pos);
}
void GameSpace::makeGameSpace(Core::RGB color, float width, float height, Vector2D pos) {
	myShip.init(width/2,height/2,this);
	min = pos+Vector2D(0,0);
	max = pos+Vector2D(width,height);
	Vector2D one   = min;
	Vector2D two   = pos+Vector2D(width,0);
	Vector2D three = max;
	Vector2D four  = pos+Vector2D(0,height);
	toDraw.initialize(color, 4, one,two,three,four);
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
}
bool GameSpace::update(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	myShip.update(dt);
	return false;
}
Boundary *GameSpace::getBoundary() { return boundary; }
Vector2D GameSpace::getMin() { return min; }
Vector2D GameSpace::getMax() { return max; }
Vector2D GameSpace::collideVector(Vector2D& pos, Vector2D& vel) {
	if(hasBounds) {
		return boundary->collideVector(pos,vel);
	} else {
		if(pos.getX() < min.getX() || pos.getX() > max.getX()) return Vector2D(-vel.getX(), vel.getY());
		if(pos.getY() < min.getY() || pos.getY() > max.getY()) return Vector2D( vel.getX(),-vel.getY());
		return vel;
	}
}