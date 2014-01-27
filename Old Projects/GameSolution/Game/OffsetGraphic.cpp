#include "OffsetGraphic.h"

void OffsetGraphic::init(const Vector2D& offset, float width, float height) {
	transpose    = offset;
	this->width  = width;
	this->height = height;
}
void OffsetGraphic::drawLine(Vector2D p1, Vector2D p2) {
	p1 = globalTrans * p1+transpose;
	p2 = globalTrans * p2+transpose;
	masterGraphic->DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}