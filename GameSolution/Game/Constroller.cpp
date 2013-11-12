#include "Controller.h"
#include "MyRandom.h"

void generateRandomPolygon(Vector2D *points, int sides, float wallLength) {
	float anglesInCircle = 2*3.14f;
	float variancePercent = 2;
	float averageAngle = anglesInCircle/sides;
	float variance = averageAngle / variancePercent;
	Vector2D lastWall = wallLength * Vector2D(Random::randomFloat(0,100),Random::randomFloat(0,100)).normalized();//some random seedVector
	for(int i=0;i<sides;i++) {
		float angle = -averageAngle+Random::randomFloat(-variance,variance);
		Vector2D newWall = Matrix3D::rotationMatrix(angle) * lastWall;
		lastWall = newWall;
		points[i] = newWall;
	}
}

#define MAX_POINTS 1000


Controller::Controller (int width, int height) :
width(width), 
height(height), 
hud(width,height),
myWorld(hud.getWorldWidth(),hud.getWorldHeight(),hud.getWorldoffset()) {
#ifdef DEBUG_CONTROLLER
	FPS = 0;
#endif//DEBUG_CONTROLLER
	setDynamicBounds();
	myWorld.registerBoundary(&bounds);
}
void Controller::setStaticBounds() {
	float padding = 5;
	float worldWidth    = hud.getWorldWidth();
	float worldHeight   = hud.getWorldHeight();
	Vector2D worldPos   = hud.getWorldoffset();
	Vector2D boundPoints[10];
	
	int numOfBoundPoints = 0;
	boundPoints[numOfBoundPoints++] = worldPos+Vector2D(padding,padding);//top right
	boundPoints[numOfBoundPoints++] = worldPos+Vector2D(padding,      (worldPos.getY()+worldHeight)/2-padding);//left
	boundPoints[numOfBoundPoints++] = worldPos+Vector2D(.1f*worldWidth,(worldHeight)-padding);
	boundPoints[numOfBoundPoints++] = Vector2D(.5f*worldWidth,        (worldPos.getY()+worldHeight)-padding);
	boundPoints[numOfBoundPoints++] = worldPos+Vector2D(worldWidth-padding,   worldHeight/2);
	boundPoints[numOfBoundPoints++] = worldPos+Vector2D(.7f*worldWidth, padding);
	
	bounds.init(numOfBoundPoints,boundPoints);
}
void Controller::setDynamicBounds() {
	Vector2D randomPoly[MAX_POINTS];
	float padding = 5;
	float sizeOfWalls = 5;
	float worldWidth    = hud.getWorldWidth();
	float worldHeight   = hud.getWorldHeight();

	int sides = Random::randomInt(4,9);
	generateRandomPolygon(randomPoly, sides, sizeOfWalls);//stored in randomPoly
	
	float polyWidth  = 2 * sizeOfWalls;
	float polyHeight = 2 * sizeOfWalls;
	float scaleX = (worldWidth  - 2 * padding) / polyWidth;
	float scaleY = (worldHeight - 2 * padding) / polyHeight;
	Matrix3D scaler = Matrix3D::translate(myWorld.getCenter()+Vector2D(padding,padding)) * Matrix3D::scaleX(scaleX) * Matrix3D::scaleY(scaleY);
		
	bounds.init(sides,randomPoly,scaler);

}
bool Controller::update(float dt) {
#ifdef DEBUG_CONTROLLER
	FPS = (int)(1/dt);
#endif//DEBUG_CONTROLLER
	return myWorld.update(dt);
}
void Controller::draw(Core::Graphics& graphics) {
	hud.draw(graphics);
	myWorld.draw(graphics);
#ifdef DEBUG_CONTROLLER
	std::stringstream ss;
	ss << FPS;
	std::string fps = ss.str();
	graphics.DrawString(0,0,fps.c_str());
#endif//DEBUG_CONTROLLER
}