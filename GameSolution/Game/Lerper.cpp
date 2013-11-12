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
Shape Lerper::myStyle(
						Lerper::myColor,
						sizeof(star)/sizeof(*star),
						star[0],
						star[1],
						star[2],
						star[3],
						star[4]
					);

void Lerper::init() {
	currentLine = 0;
	pathLength  = 0;
	alpha=10;
}
void Lerper::addPoint(const Vector2D& toAdd) {
	assert(pathLength!=MAX_PATH_LENGTH);
	path[pathLength++] = toAdd;
}
int  Lerper::nextIndex() {
	return (currentLine+1)%pathLength;
}
void Lerper::nextLine() {
	currentLine  = nextIndex();
	catchedNextLine = path[nextIndex()];
	//interval = (float)(catchedNextLine-path[currentLine]).lengthSquared()/distacePerSecond;
	Vector2D temp = catchedNextLine-path[currentLine];
	float length = (float)temp.length();
	interval = 1/(length/distacePerSecond);
	alpha = 0;
}
void Lerper::update(float dt) {
	assert(pathLength>1);
	angle+=turnSpeed*dt;
	alpha+=(interval*dt);
	if(alpha>1) nextLine();
	pos = path[currentLine].LERP(alpha,catchedNextLine);
}
void Lerper::draw(Core::Graphics& graphics) {
	//float scale = 1+2*(angle - (int)angle);
	myStyle.draw(graphics, pos, angle);
}