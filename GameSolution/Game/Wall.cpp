#include "Wall.h"

void     Wall::init(const Vector2D& start, const Vector2D& end) {
	Vector2D wallVector = end-start;
	this->start = start;//copy the memory
	this->end   = end;  //copy the memory
	norm = wallVector.perpCCW().normalized();
}
bool     Wall::hasCollided(const Vector2D& pos) {
	Vector2D ship2Wall(pos-end);
	return (ship2Wall.dot(norm)<0);
}
HitInfo  Wall::collideVector(const Vector2D& pos, const Vector2D& vel) {
	HitInfo ret(pos,vel);
	ret.hasHit = hasCollided(pos);
	if(ret.hasHit) {
		Vector2D lastPos = pos-vel;
		float distanceOne = (lastPos - start).dot(norm);
		float distanceTwo = (    pos - start).dot(norm);
		if(distanceOne>0 && distanceTwo<0) {//collision happened in last move
			ret.vel = vel-2*vel.projection(norm);
			ret.pos = lastPos;
		}
	}
	return ret;
}
void     Wall::draw(MyGraphics& graphics) {
	graphics.drawLine(start,end);
}