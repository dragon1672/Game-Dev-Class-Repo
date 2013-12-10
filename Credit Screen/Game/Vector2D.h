#ifndef Vector2D_TWO
#define Vector2D_TWO
#include <iostream>
#include <cmath>
class Vector2D {
private:
	float x;
	float y;
public:
	explicit Vector2D(float x=0, float y=0) {
		this->x = x;
		this->y = y;
	}
	//getters
	inline float getX() const;
	inline float getY() const;
	//static non member declerations
	static inline float    dot          (const Vector2D&, const Vector2D&);
	static inline float    lengthSquared(const Vector2D&);
	static inline double   length       (const Vector2D&);
	static inline Vector2D normalized   (const Vector2D&);
	static inline Vector2D perpCW       (const Vector2D&);
	static inline Vector2D perpCCW      (const Vector2D&);
	static inline Vector2D LERP         (float, const Vector2D&, const Vector2D&);
	static inline float    cross        (const Vector2D&, const Vector2D&);
	static inline Vector2D projection   (const Vector2D& left, const Vector2D& right);
	static inline Vector2D rejection    (const Vector2D& left, const Vector2D& right);
	static inline bool     isZero       (const Vector2D& toCheck);
	//Member definitons
	inline float    lengthSquared() const;
	inline double   length() const;
	inline Vector2D normalized() const;
	inline Vector2D perpCW() const;
	inline Vector2D perpCCW() const;
	inline float    dot(const Vector2D& that) const;
	inline Vector2D LERP(float percent, const Vector2D& that) const;
	inline float    cross(const Vector2D& that) const;
	inline Vector2D projection(const Vector2D& that) const;
	inline Vector2D rejection (const Vector2D& that) const;
	inline bool     isZero() const;
	//overload declerations
	friend inline std::ostream& operator<<(std::ostream& stream, const Vector2D& right);
	friend inline Vector2D operator+ (const Vector2D& left, const Vector2D& right);
	friend inline Vector2D operator- (const Vector2D& left, const Vector2D& right);
	friend inline Vector2D operator- (const Vector2D& right);
	friend inline Vector2D operator* (const Vector2D& right, float constant       );
	friend inline Vector2D operator* (float constant,        const Vector2D& right);
	friend inline Vector2D operator/ (const Vector2D& right, float constant       );
	friend inline bool     operator==(const Vector2D& right, const Vector2D left  );
	inline operator float*();
};
//inlines
//getters
float Vector2D::getX() const { return x; }
float Vector2D::getY() const { return y; }
//static defines
float    Vector2D::lengthSquared(const Vector2D& src) {
	return dot(src,src);
}
double   Vector2D::length       (const Vector2D& src) {
	return sqrt(lengthSquared(src));
}
Vector2D Vector2D::normalized   (const Vector2D& src) {
	float Vlength = (float)length(src);
	return (Vlength==0)? Vector2D(0,0) : src/Vlength;
}
Vector2D Vector2D::perpCW       (const Vector2D& src) {
	return Vector2D(-(src.y),src.x);
}
Vector2D Vector2D::perpCCW      (const Vector2D& src) {
	return Vector2D(src.y,-(src.x));
}
float    Vector2D::dot          (const Vector2D& left, const Vector2D& right) {
	return (left.x * right.x) + (left.y * right.y);
}
Vector2D Vector2D::LERP         (float percent,  const Vector2D& right, const Vector2D& left) {
	return (1-percent) * right + (percent * left);
}
float    Vector2D::cross        (const Vector2D& left, const Vector2D& right) {
	return left.x * right.y - left.y * right.x;
}
Vector2D Vector2D::projection   (const Vector2D& left, const Vector2D& right) {
	return (left.dot(right) * right) / right.lengthSquared();
}
Vector2D Vector2D::rejection (const Vector2D& left, const Vector2D& right) {
	return left - left.projection(right);
}
bool     Vector2D::isZero(const Vector2D& toCheck) {
	return (toCheck.x==0 && toCheck.y==0);
}
//member functions
float    Vector2D::lengthSquared() const {
	return lengthSquared(*this);
}
double   Vector2D::length() const {
	return length(*this);
}
Vector2D Vector2D::normalized() const {
	return normalized(*this);
}
Vector2D Vector2D::perpCW() const {
	return perpCW(*this);
}
Vector2D Vector2D::perpCCW() const {
	return perpCCW(*this);
}
float    Vector2D::dot(const Vector2D& that) const {
	return dot(*this,that);
}
Vector2D Vector2D::LERP(float percent, const Vector2D& that) const {
	return LERP(percent,*this,that);
}
float    Vector2D::cross(const Vector2D& that) const {
	return cross(*this,that);
}
Vector2D Vector2D::projection(const Vector2D& that) const {
	return projection(*this,that);
}
Vector2D Vector2D::rejection (const Vector2D& that) const {
	return rejection(*this,that);
}
bool     Vector2D::isZero() const {
	return isZero(*this);
}
//overloads
std::ostream& operator<<(std::ostream& stream, const Vector2D& right) {
	std::cout << "{" << right.x << ", " << right.y << "}";
	return stream;
}
Vector2D operator+ (const Vector2D& left,  const Vector2D& right) {
	return Vector2D(left.x + right.x, left.y + right.y);
}
Vector2D operator- (const Vector2D& left,  const Vector2D& right) {
	return Vector2D(left.x - right.x, left.y - right.y);
}
Vector2D operator- (const Vector2D& right) {
	return Vector2D(-right.x, -right.y);
}
Vector2D operator* (const Vector2D& right, float constant) {
	return Vector2D(right.x * constant, right.y * constant);
}
Vector2D operator* (float constant, const Vector2D& right) {
	return right * constant;
}
Vector2D operator/ (const Vector2D& right, float constant     ) {
	return Vector2D(right.x / constant, right.y / constant);
}
bool     operator==(const Vector2D& right, const Vector2D left  ) {
	return (right.x==left.x && right.y==left.y);
}
Vector2D::operator float*() {
	return &x;
}
#endif