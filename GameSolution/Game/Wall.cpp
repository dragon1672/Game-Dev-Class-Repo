#include "Wall.h"

void Wall::init(Vector2D start, Vector2D end) {
	this->start = start;
	this->end   = end;
	wallVector = end-start;
	norm = wallVector.perpCCW().normalized();
}
bool Wall::hasCollided(Vector2D pos) {
	Vector2D ship2Wall(pos-end);
	return (ship2Wall.dot(norm)<0);
}
Vector2D Wall::collideVector(Vector2D pos, Vector2D vel) {
	if(hasCollided(pos)) {
		return vel-2*vel.projection(norm);//amount that it reflects
	}
	return vel;
}
void Wall::draw(Core::Graphics graphics) {
	graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
}