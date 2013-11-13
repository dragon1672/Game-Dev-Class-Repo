#include "SimpleBounary.h"

void SimpleBoundary::init(float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}
bool     SimpleBoundary::hasCollided  (const Vector2D& pos) {
	return (pos.getX()<x1
		 || pos.getY()<y1
		 || pos.getX()>x2
		 || pos.getY()>y2);

}
Vector2D SimpleBoundary::collideVector(const Vector2D& pos, const Vector2D& vel) {
	if(pos.getX() < x1 || pos.getX() > x2) return Vector2D(-vel.getX(), vel.getY());
	if(pos.getY() < y1 || pos.getY() > y2) return Vector2D( vel.getX(),-vel.getY());
	return vel;

}
void     SimpleBoundary::draw(Core::Graphics& graphics) {
	graphics.SetColor(defaultColor);
	graphics.DrawLine(x1,y1,x1,y2);//left wall
	graphics.DrawLine(x1,y2,x2,y2);//bottom wall
	graphics.DrawLine(x2,y2,x2,y1);//right wall
	graphics.DrawLine(x1,y1,x2,y1);//top wall
}