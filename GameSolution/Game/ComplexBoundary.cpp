#include "ComplexBoundary.h"

void      ComplexBoundary::init(int count, Vector2D *points, const Matrix3D& transform) {
	numOfWalls = count;
	for(int i=0;i<numOfWalls;i++) {
		Vector2D start = transform * points[i];
		Vector2D end   = transform * points[(i+1)%numOfWalls];
		walls[i].init(start,end);
	}
}
bool      ComplexBoundary::hasCollided  (const Vector2D& pos) {
	for(int i=0;i<numOfWalls;i++) {
		if(walls[i].hasCollided(pos)) return true;
	}
	return false;
}
Vector2D  ComplexBoundary::collideVector(const Vector2D& pos, const Vector2D& vel) {
	Vector2D ret = vel;
	for(int i=0;i<numOfWalls;i++) {
		if(walls[i].hasCollided(pos)) {
			ret = walls[i].collideVector(pos,vel);
		}
	}
	return ret;
}
void      ComplexBoundary::draw(Core::Graphics& graphics) {
	graphics.SetColor(defaultColor);
	for(int i=0;i<numOfWalls;i++) {
		walls[i].draw(graphics);
	}
}