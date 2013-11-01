#include "Boundary.h"

Core::RGB Boundary::defaultColor = RGB(220,208,255);

void Boundary::init(int count,...) {
	va_list points;
	va_start(points,count);
	Vector2D *t_points = new Vector2D[count];
	for(int i=0;i<count;i++) {
		t_points[i] = va_arg(points, Vector2D);
	}
	init(count,t_points);
	delete [] t_points;
}
void Boundary::init(int count, Vector2D *points) {
	numOfWalls = count;
	walls = new Wall[numOfWalls];
	for(int i=0;i<numOfWalls;i++) {
		Vector2D& start = points[i];
		Vector2D& end   = points[(i+1)%numOfWalls];
		walls[i].init(start,end);
	}
	started = true;
}
bool Boundary::hasCollided(Vector2D pos) {
	for(int i=0;i<numOfWalls;i++) {
		if(walls[i].hasCollided(pos)) return true;
	}
	return false;
}
Vector2D Boundary::collideVector(Vector2D pos, Vector2D vel) {
	if(started) {
		for(int i=0;i<numOfWalls;i++) {
			if(walls[i].hasCollided(pos)) {
				return walls[i].collideVector(pos,vel);
			}
		}
	}
	return vel;
}
void Boundary::draw(Core::Graphics graphics) {
	graphics.SetColor(defaultColor);
	if(started) {
		for(int i=0;i<numOfWalls;i++) {
			walls[i].draw(graphics);
		}
	}
}