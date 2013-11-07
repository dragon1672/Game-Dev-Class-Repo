#include "Wall.h"

void     Wall::init(const Vector2D& start, const Vector2D& end) {
	Vector2D wallVector = end-start;
	this->start = start;//copy the memory
	this->end   = end;//copy the memory
	norm = wallVector.perpCCW().normalized();
}
bool     Wall::hasCollided(const Vector2D& pos) {
	Vector2D ship2Wall(pos-end);
	return (ship2Wall.dot(norm)<0);
}
Vector2D Wall::collideVector(const Vector2D& pos, const Vector2D& vel) {
	Vector2D ret = vel;
	if(hasCollided(pos)) {
		Vector2D lastPos = pos-vel;
		//*
		float distanceOne = (lastPos - start).dot(norm);
		float distanceTwo = (    pos - start).dot(norm);
		if(distanceOne>0 && distanceTwo<0) {//collision happened in last move
			ret = vel-2*vel.projection(norm);
		}//*/
		/*
		Vector2D resultVel = vel-2*vel.projection(norm);//amount that it reflects
		if(hasCollided(pos+resultVel)) return vel;//result has already been calculated
		return resultVel;
		//*/
	}
	return ret;
}
void     Wall::draw(Core::Graphics& graphics) {
	graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
}

/*
float distanceOne = (previousPos - wallStart).dot(wallNorm);
float distanceTwo = (pos - wallStart).dot(wallNorm);
if(distanceOne>0 && distanceTwo<0) {//magic
	result = vel-2*projection(norm);
	return result;
}
return vel

//*/