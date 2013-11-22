#include "Lerper.h"

#define SCALAR 20
Vector2D star[] = {
						SCALAR*Vector2D(   .7f,  1.0f ),//1
						SCALAR*Vector2D(  0.0f, -1.0f ),//2
						SCALAR*Vector2D(  -.6f,  1.0f ),//3
						SCALAR*Vector2D(  1.0f,  -.25f),//4
						SCALAR*Vector2D( -1.0f,  -.25f) //5
					};
Core::RGB Lerper::myColor = RGB(255,102,255);
float Lerper::turnSpeed = 5;
const float Lerper::FULL_STARTING_HEALTH=5;
Shape Lerper::myStyle(
						Lerper::myColor,
						SIZE_OF_ARRAY(star),
						star[0],
						star[1],
						star[2],
						star[3],
						star[4]
					);

void Lerper::init() {
	currentLine = 0;
	pathIndex  = 0;
	alpha=10;
	bodyGuards.startup(5);
	initFullHealth(FULL_STARTING_HEALTH);
}
void Lerper::addPoint(const Vector2D& toAdd) {
	MY_ASSERT(pathIndex!=MAX_PATH_LENGTH);
	path[pathIndex++] = toAdd;
}
int  Lerper::nextIndex() {
	return (currentLine+1)%pathIndex;
}
void Lerper::nextLine() {
	currentLine  = nextIndex();
	catchedNextLine = path[nextIndex()];
	Vector2D temp = catchedNextLine-path[currentLine];
	float length = (float)temp.length();
	interval = 1/(length/distacePerSecond);
	alpha = 0;
}
Matrix3D Lerper::getTransMatrix() {
	return Matrix3D::translate(pos) * Matrix3D::rotationMatrix(angle);
}
void Lerper::update(float dt) {
	MY_ASSERT(pathIndex>1);
	angle+=turnSpeed*dt;
	alpha+=(interval*dt);
	if(alpha>1) nextLine();
	pos = path[currentLine].LERP(alpha,catchedNextLine);
	bodyGuards.update(dt);
}
Shape* Lerper::getStyle() {
	return &myStyle;
}
void Lerper::draw(Core::Graphics& graphics) {
	getStyle()->draw(graphics, getTransMatrix());
	bodyGuards.draw(graphics,Matrix3D::translate(pos) * Matrix3D::rotationMatrix(angle));
}
int Lerper::getTeam() {
	return NEUTRAL_TEAM;
}
Vector2D Lerper::getPos() {
	return pos;
}