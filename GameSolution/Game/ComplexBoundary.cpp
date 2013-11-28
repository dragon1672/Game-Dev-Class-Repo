#include "ComplexBoundary.h"
#include <cassert>

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
HitInfo   ComplexBoundary::collideVector(const Vector2D& pos, const Vector2D& vel) {
	HitInfo ret(pos,vel);
	ret.hasHit = false;
	for(int i=0;i<numOfWalls && !ret.hasHit;i++) {
		if(walls[i].hasCollided(pos)) {
			ret = walls[i].collideVector(pos,vel);
			MY_ASSERT(ret.hasHit==true);
		}
	}
	return ret;
}
void      ComplexBoundary::draw(MyGraphics& graphics) {
	graphics.setColor(defaultColor);
	for(int i=0;i<numOfWalls;i++) {
		walls[i].draw(graphics);
	}
}