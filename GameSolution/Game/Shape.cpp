#include <random>
#include "Shape.h"


std::random_device rd;//creating engine
std::mt19937 seed(rd()); //seed
std::uniform_int_distribution<int>randColor(0,255);

#define RANDOM_COLOR RGB(randColor(seed),randColor(seed),randColor(seed))
const Core::RGB defaultColor = RGB(0,255,0);
/*Shape::Shape(int count,...) {
	constructed = false;
	va_list temp;
	va_start(temp,count);
	initialize(defaultColor,count,temp);
}//*/
Shape::Shape(Core::RGB color, int count,...) {
	constructed = false;
	va_list temp;
	va_start(temp,count);
	initialize(color,Matrix3D(),count,temp);
}
Shape::Shape(Core::RGB color, const Matrix3D& trans, int count,...) {
	constructed = false;
	va_list temp;
	va_start(temp,count);
	initialize(color,trans,count,temp);
}
Shape::Shape() {
	constructed = false;
	count = 0;
}
void Shape::destory() {
	if(constructed) delete [] points;
	constructed = false;
}
Shape::~Shape() {
	destory();
}
bool Shape::initialize(Core::RGB color, const Matrix3D& transform, int count,...) {
	va_list temp;
	va_start(temp,count);
	return initialize(color,transform,count,temp);
}
bool Shape::initialize(Core::RGB color, const Matrix3D& transform, int count, va_list toStore) {
	if(count>1 && !constructed) {
		constructed = true;
		this->count = count;
		points = new Vector2D[count];
		for(int i=0;i<count;i++) {
			points[i] = transform * va_arg(toStore, Vector2D);
		}
		calcMinAndMax();
		setColor(color);
	}
	va_end(toStore);
	return constructed;
}
bool Shape::initialize(Core::RGB color, const Matrix3D& transform, int count, Vector2D *toAdd) {
	if(count>1 && !constructed) {
		constructed = true;
		this->count = count;
		points = new Vector2D[count];
		for(int i=0;i<count;i++) {
			points[i] = transform * toAdd[i];
		}
		calcMinAndMax();
		setColor(color);
	}
	delete [] toAdd;
	return constructed;
}
void Shape::setColor(Core::RGB toSet) {
	myColor = toSet;
}
void Shape::setRandomColor() {
	myColor = RANDOM_COLOR;
}
void Shape::calcMinAndMax() {
	maxX = points[0].getX();
	maxY = points[0].getY();
	minX = points[0].getX();
	minY = points[0].getY();
	for(int i=0;i<count;i++) {
		if(points[i].getX()>maxX) maxX = points[i].getX();
		if(points[i].getY()>maxY) maxY = points[i].getY();
		if(points[i].getX()<minX) minX = points[i].getX();
		if(points[i].getY()<minY) minY = points[i].getY();
	}
}
#ifdef DEBUG_SHAPE
	#include <sstream>
	#include <string>
	using std::string;
	string float2str(int num) {
		std::stringstream ss;
		string ret;
		ss << num;
		ss >> ret;
		return ret;
	}
	string vec2str(Vector2D vec) {
		string ret = "{"+float2str(vec.getX())+","+float2str(vec.getY())+"}";
		return ret;
	}
#endif //DEBUG_SHAPE
void Shape::draw(Core::Graphics& graphics, const Matrix3D& transform) {
	if(constructed) {
		graphics.SetColor(myColor);
		Vector2D start = transform*points[0];
		Vector2D end   = transform*points[count-1];
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		for(int i=1;i<count;i++) {
			start = transform*points[i-1];
			end   = transform*points[i];
			graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
#ifdef DEBUG_SHAPE
			graphics.DrawString(start.getX(),start.getY(),vec2str(start).c_str());
			graphics.DrawString(end.getX(),  end.getY(),  vec2str(end).c_str());
#endif //DEBUG_SHAPE
		}
	}
}
//
/*(Luis) If possible, specify the differences between these two draw functions.  They see, fairly similar aside from the "scale" parameters*/
void Shape::draw(Core::Graphics& graphics, const Vector2D& transpose, float rotation, float scale) {
	draw(graphics,transpose,rotation,scale,scale);
}
void Shape::draw(Core::Graphics& graphics, const Vector2D& transpose, float rotation, float scaleX, float scaleY) {
	Matrix3D transform = Matrix3D::translate(transpose) * Matrix3D::rotationMatrix(rotation) * Matrix3D::scaleX(scaleX) * Matrix3D::scaleX(scaleY);
	draw(graphics,transform);
}
//
bool Shape::isConstructed() {
	return constructed;
}