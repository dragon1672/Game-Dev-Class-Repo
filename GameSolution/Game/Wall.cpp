#include "Wall.h"

void Wall::init(Vector2D start, Vector2D end) {
	Vector2D wallVector = end-start;
	this->start = start;// - wallVector.normalized();
	this->end   = end;//   + wallVector.normalized();
	norm = wallVector.perpCCW().normalized();
}
bool Wall::hasCollided(Vector2D pos) {
	Vector2D ship2Wall(pos-end);
	return (ship2Wall.dot(norm)<0);
}
Vector2D Wall::collideVector(Vector2D pos, Vector2D vel) {
	if(hasCollided(pos)) {
		Vector2D lastPos = pos-vel;
		//*
		float distanceOne = (lastPos - start).dot(norm);
		float distanceTwo = (    pos - start).dot(norm);
		if(distanceOne>0 && distanceTwo<0) {//collision happened in last move
			return vel-2*vel.projection(norm);
		}//*/
		/*
		Vector2D resultVel = vel-2*vel.projection(norm);//amount that it reflects
		if(hasCollided(pos+resultVel)) return vel;//result has already been calculated
		return resultVel;
		//*/
	}
	return vel;
}
void Wall::draw(Core::Graphics graphics) {
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