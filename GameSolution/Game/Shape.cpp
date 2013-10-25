#include "Shape.h"
Shape::Shape(int count,...) {
		this->count = count;
		points = new Vector2D[count];
		va_list toStore;
		va_start(toStore,count);
		for(int i=0;i<count;i++) {
			points[i] = va_arg(toStore, Vector2D);
		}
		va_end(toStore);
		calcMinAndMax();
	}
void Shape::calcMinAndMax() {
	maxX = points[0].getX();
	maxY = points[0].getY();
	minX = points[0].getX();
	minY = points[0].getY();
	for(int i=0;i<count;i++) {
		if(points[0].getX()>maxX) maxX = points[i].getX();
		if(points[0].getY()>maxY) maxY = points[i].getX();
		if(points[0].getX()<minX) minX = points[i].getX();
		if(points[0].getY()<minY) minY = points[i].getX();
	}
}
void Shape::draw(Core::Graphics graphics, Vector2D transpose, int scale) {
	graphics.DrawLine(points[0].getX(), points[0].getY(),points[count-1].getX(),points[count-1].getY());
	for(int i=1;i<count-1;i++) {
		Vector2D start = transpose+scale*points[i-1];
		Vector2D end   = transpose+scale*points[i];
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
	}
}