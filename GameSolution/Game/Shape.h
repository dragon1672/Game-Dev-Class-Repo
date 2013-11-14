#pragma once


#pragma warning(disable:4005)//warning has been suppressed at a Visual Studio Level
#include <stdarg.h>
#pragma warning(default:4005)
#include "Vector 2.h"
#include "Matrix3D.h"
#include "Core.h"

//#define DEBUG_SHAPE

class Shape {
protected:
	void destory();
	Vector2D *points;
	int count;
private:
	bool constructed;
	float maxX;
	float maxY;
	float minX;
	float minY;
	Core::RGB myColor;
	void calcMinAndMax();
public:
	Shape();
	Shape(Core::RGB color, int count,...);
	Shape(Core::RGB color, const Matrix3D& transformations, int count,...);
	~Shape();
	bool initialize(Core::RGB, const Matrix3D& transform, int count,...);
	bool initialize(Core::RGB, const Matrix3D& transform, int count, va_list toStore);
	bool initialize(Core::RGB, const Matrix3D& transform, int count, Vector2D *toAdd);
	void draw(Core::Graphics& graphics, const Vector2D& transpose=Vector2D(0,0), float rotation=0, float scale=1);
	void draw(Core::Graphics& graphics, const Vector2D& transpose, float rotation, float scaleX, float scaleY);
	void draw(Core::Graphics& graphics, const Matrix3D& transform);

	//collision to point
	bool circleCollisionCheck(const Vector2D& toCheck, const Matrix3D& transformations) {
		Vector2D center = transformations * Vector2D(0,0);
		if( (center - toCheck).lengthSquared() < getRadius() ) return true;
		return false;
	}
	bool collision(const Vector2D& toCheck, const Matrix3D& transformations) {
		return circleCollisionCheck(toCheck,transformations);
	}
	//collision to shape

	bool circleCollisionCheck(const Shape& toCheck, const Matrix3D& trans, const Matrix3D& transForCheck) {
		Vector2D center1 = trans * Vector2D(0,0);
		Vector2D center2 = transForCheck * Vector2D(0,0);
		if( (center1 - center2).lengthSquared()<(this->getRadius() + toCheck.getRadius()) ) return true;
		return false;
	}
	bool collision(const Shape& toCheck, const Matrix3D& trans, const Matrix3D& transForCheck) {
		return circleCollisionCheck(toCheck,trans,transForCheck);
	}


	void setRandomColor();
	void setColor(Core::RGB toSet);
	bool isConstructed();
	inline float getRadius() const { return (getWidth() > getHeight())? getWidth() : getHeight(); }
	inline float getMinX()   const { return minX; }
	inline float getMinY()   const { return minY; }
	inline float getMaxX()   const { return maxX; }
	inline float getMaxY()   const { return maxY; }
	inline float getHeight() const { return getMaxY() - getMinY(); }
	inline float getWidth()  const { return getMaxX() - getMinX(); }
};
