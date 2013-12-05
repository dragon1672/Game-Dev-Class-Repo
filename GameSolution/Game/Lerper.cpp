#include "Lerper.h"
#include "GameMacros.h"
#include "TeamInfo.h"

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
const float Lerper::FULL_STARTING_HEALTH=20;
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
	LOG(Info,"Lerper Init",0);
	currentLine    = 0;
	numOfWayPoints = 0;
	alpha=10;
	bodyGuards.startup(3,3);
	initFullHealth(FULL_STARTING_HEALTH);
}
void Lerper::addPoint(const Vector2D& toAdd) {
	ASSERT(numOfWayPoints!=MAX_PATH_LENGTH,"Array length for lerper exceeded");
	path[numOfWayPoints++] = toAdd;
}
int  Lerper::nextIndex() {
	return (currentLine+1)%numOfWayPoints;
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
	ASSERT(numOfWayPoints>1,"");
	angle+=turnSpeed*dt;
	alpha+=(interval*dt);
	if(alpha>1) nextLine();
	pos = path[currentLine].LERP(alpha,catchedNextLine);
	bodyGuards.update(dt);
}
Shape* Lerper::getStyle() {
	return &myStyle;
}
void Lerper::draw(MyGraphics& graphics) {
	getStyle()->draw(graphics, getTransMatrix());
	bodyGuards.draw(graphics,Matrix3D::translate(pos));
}
int Lerper::getTeam() {
	return TeamInfo::NEUTRAL_TEAM;
}
Vector2D Lerper::getPos() {
	return pos;
}