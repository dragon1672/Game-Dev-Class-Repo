#include "Shape.h"
Shape::Shape(int count,...) {
	if(count!=0) {
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
}
Shape::Shape() {
	count = 0;
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
void Shape::draw(Core::Graphics graphics, Vector2D transpose, float scale) {
	if(count!=0) {
		Vector2D start = transpose+scale*points[0];
		Vector2D end   = transpose+scale*points[count-1];
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		for(int i=1;i<count;i++) {
			start = transpose+scale*points[i-1];
			end   = transpose+scale*points[i];
			graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		}
	}
}