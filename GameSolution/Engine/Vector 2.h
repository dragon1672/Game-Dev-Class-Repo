#ifndef Vector2D_TWO
#define Vector2D_TWO
#include <iostream>
#include <cmath>
struct Vector2D {
private:
	float x;
	float y;
public:
	explicit Vector2D(float x=0, float y=0) {
		this->x = x;
		this->y = y;
	}
	//getters
	float getX();
	float getY();
	//static non member declerations
	static inline float    dot(Vector2D&,  Vector2D&);
	static inline float    lengthSquared(Vector2D&);
	static inline double   length(Vector2D&);
	static inline Vector2D normalized(Vector2D&);
	static inline Vector2D perpCW (Vector2D&);
	static inline Vector2D perpCCW(Vector2D&);
	static inline Vector2D LERP(float, Vector2D&, Vector2D&);
	static inline float    cross(Vector2D&, Vector2D&);
	static inline Vector2D projection(Vector2D& left, Vector2D& right);
	static inline Vector2D rejection (Vector2D& left, Vector2D& right);
	//Member definitons
	inline float    lengthSquared();
	inline double   length();
	inline Vector2D normalized();
	inline Vector2D perpCW();
	inline Vector2D perpCCW();
	inline float    dot(Vector2D& that);
	inline Vector2D LERP(float percent, Vector2D& that);
	inline float    cross(Vector2D& that);
	inline Vector2D projection(Vector2D& that);
	inline Vector2D rejection (Vector2D& that);
	//overload declerations
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& right);
	friend Vector2D operator+(const Vector2D& left,           const Vector2D& right);
	friend Vector2D operator-(const Vector2D& left,           const Vector2D& right);
	friend Vector2D operator-(const Vector2D& right);
	friend Vector2D operator*(const Vector2D& right,  float constant     );
	friend Vector2D operator*(float constant,       const Vector2D& right);
	friend Vector2D operator/(const Vector2D& right,  float constant     );
	operator float*();
};
//overloads
std::ostream& operator<<(std::ostream& stream, const Vector2D& right);
Vector2D operator+(const Vector2D& left,  const Vector2D& right);
Vector2D operator-(const Vector2D& left, const Vector2D& right);
Vector2D operator-(const Vector2D& right);
Vector2D operator*(const Vector2D& right, float constant);
Vector2D operator*(float constant, const Vector2D& right);
Vector2D operator/(const Vector2D& right, float constant);
#include "Vector 2.inl"
#endif