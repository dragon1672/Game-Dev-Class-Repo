//getters
float Vector2D::getX() { return x; }
float Vector2D::getY() { return y; }
//static defines
float    Vector2D::lengthSquared(Vector2D& src) {
	return dot(src,src);
}
double   Vector2D::length(Vector2D& src) {
	return sqrt(lengthSquared(src));
}
Vector2D Vector2D::normalized(Vector2D& src) {
	float Vlength = length(src);
	return (Vlength==0)? Vector2D(0,0) : src/Vlength;
}
Vector2D Vector2D::perpCW(Vector2D& src) {
	return Vector2D(-(src.y),src.x);
}
Vector2D Vector2D::perpCCW(Vector2D& src) {
	return Vector2D(src.y,-(src.x));
}
float    Vector2D::dot(Vector2D& left, Vector2D& right) {
	return (left.x * right.x) + (left.y * right.y);
}
Vector2D Vector2D::LERP(float percent, Vector2D& right, Vector2D& left) {
	//if(percent>1) percent = fmod(percent,1.0);
	return (1-percent) * right + (percent * left);
}
float    Vector2D::cross(Vector2D& left, Vector2D& right) {
	return left.x * right.y - left.y * right.x;
}
Vector2D Vector2D::projection(Vector2D& left, Vector2D& right) {
	return right.normalized() * left.dot(right.normalized());
}
Vector2D Vector2D::rejection (Vector2D& left, Vector2D& right) {
	return left - left.projection(right);
}
//member functions
float    Vector2D::lengthSquared() {
	return lengthSquared(*this);
}
double   Vector2D::length() {
	return length(*this);
}
Vector2D Vector2D::normalized() {
	return normalized(*this);
}
Vector2D Vector2D::perpCW() {
	return perpCW(*this);
}
Vector2D Vector2D::perpCCW() {
	return perpCCW(*this);
}
float    Vector2D::dot(Vector2D& that) {
	return dot(*this,that);
}
Vector2D Vector2D::LERP(float percent, Vector2D& that) {
	return LERP(percent,*this,that);
}
float    Vector2D::cross(Vector2D& that) {
	return cross(*this,that);
}
Vector2D Vector2D::projection(Vector2D& that) {
	return projection(*this,that);
}
Vector2D Vector2D::rejection (Vector2D& that) {
	return rejection(*this,that);
}
//overloads
std::ostream& operator<<(std::ostream& stream, const Vector2D& right) {
	std::cout << "{" << right.x << ", " << right.y << "}";
	return stream;
}
Vector2D operator+(const Vector2D& left,  const Vector2D& right) {
	return Vector2D(left.x + right.x, left.y + right.y);
}
Vector2D operator-(const Vector2D& left, const Vector2D& right) {
	return Vector2D(left.x - right.x, left.y - right.y);
}
Vector2D operator-(const Vector2D& right) {
	return Vector2D(-right.x, -right.y);
}
Vector2D operator*(const Vector2D& right, float constant) {
	return Vector2D(right.x * constant, right.y * constant);
}
Vector2D operator*(float constant, const Vector2D& right) {
	return right * constant;
}
Vector2D operator/(const Vector2D& right, float constant     ) {
	return Vector2D(right.x / constant, right.y / constant);
}
Vector2D::operator float*() {
	return &x;
}