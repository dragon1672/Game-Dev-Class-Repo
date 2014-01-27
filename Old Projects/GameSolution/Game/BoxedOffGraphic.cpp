#include "BoxedOffGraphic.h"

bool BoxedOffGraphic::isInBox(Vector2D& pos2Check,Vector2D&boxLocation,int width, int height) {
		Vector2D checking = pos2Check - boxLocation;
		return (0<=checking.getX() && checking.getX() <= width
				&& 0<=checking.getY() && checking.getY() <= height);
	}
void BoxedOffGraphic::init(const Vector2D& pos, float width, float height) {
	this->pos    = pos;
	this->width  = width;
	this->height = height;
}
void BoxedOffGraphic::drawLine(Vector2D p1, Vector2D p2) {
	if(isInBox(p1,pos,(int)width,(int)height) && isInBox(p2,pos,(int)width,(int)height))//only draw if in bounds
		masterGraphic->DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}