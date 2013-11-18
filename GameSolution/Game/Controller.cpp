#include "Controller.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"

void generateRandomPolygon(Vector2D *points, int sides, float wallLength) {
	float anglesInCircle = 2*3.14f;
	float variancePercent = 4;
	float averageAngle = anglesInCircle/sides;
	float variance = averageAngle / variancePercent;
	Vector2D lastWall = wallLength * Random::randomUnitVector();//Vector2D(Random::randomFloat(0,100),Random::randomFloat(0,100)).normalized();//some random seedVector
	for(int i=0;i<sides;i++) {
		float angle = -averageAngle+Random::randomFloat(-variance,variance);
		Vector2D newWall = Matrix3D::rotationMatrix(angle) * lastWall;
		lastWall = newWall;
		points[i] = newWall;
	}
}

#define MAX_POINTS 1000


Controller::Controller (int width, int height) : width(width), 
												 height(height), 
												 hud(width,height),
												 KEY_C('C'),
												 KEY_X('X'),
												 PAUSE_BUTTON('P'),
												 myWorld(hud.getWorldWidth(),hud.getWorldHeight(),hud.getWorldoffset()) {
#ifdef DEBUG_Controller
	FPS = 0;
#endif//DEBUG_Controller
	setDynamicBounds();
	initSimpleBounds();
	currentBounds = &complexBounds;
	myWorld.registerBoundary(currentBounds);
}
void Controller::initSimpleBounds() {
	float startX = myWorld.getMin().getX();
	float startY = myWorld.getMin().getY();
	float endX   = myWorld.getMax().getX();
	float endY   = myWorld.getMax().getY();
	simpleBounds.init(startX,startY,endX,endY);

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
	
	complexBounds.init(numOfBoundPoints,boundPoints);
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
		
	complexBounds.init(sides,randomPoly,scaler);

}
void Controller::updateCurrentBounds() {
	if(KEY_X.hasBeenClicked()) currentBounds = &simpleBounds;
	if(KEY_C.hasBeenClicked()) currentBounds = &complexBounds;
}

bool Controller::update(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	PAUSE_BUTTON.update(dt);
	if(PAUSE_BUTTON.hasBeenClicked()) isPaused = !isPaused; /*(Luis) saying isPaused == false feels a bit more readable than !isPaused in this case*/
	if(!isPaused) {
		KEY_X.update(dt);
		KEY_C.update(dt);
		updateCurrentBounds();
		myWorld.registerBoundary(currentBounds);
		myWorld.update(dt);
	}
#ifdef DEBUG_Controller
	FPS = (int)(1/dt);
#endif//DEBUG_Controller
	return false;
}
void Controller::draw(Core::Graphics& graphics) {
	Core::RGB worldColor = RGB(0,100,0);//green
	Core::RGB pauseColor = RGB(50,50,50);

	if(currentBounds == &complexBounds) worldColor = RGB(10,10,10);
	if(currentBounds == &simpleBounds)  worldColor = RGB(0,0,10); 
	if(isPaused) worldColor = pauseColor;

	hud.draw(graphics);
	hud.paintWorld(graphics,worldColor);
	myWorld.draw(graphics);
#ifdef DEBUG_Controller
	std::stringstream ss;
	ss << FPS;
	std::string fps = ss.str();
	graphics.DrawString(0,0,fps.c_str());
#endif//DEBUG_Controller
	if(isPaused) {
		hud.worldPopup(graphics,"GAME HAS BEEN PAUSED",ExtendedGraphics::brightness(pauseColor,.5));
		//ExtendedGraphics::textInABox(graphics,ExtendedGraphics::brightness(pauseColor,.5),HUD::defaultTextColor, "GAME HAS BEEN PAUSED",hud.getWorldoffset().getX(),hud.getWorldoffset().getY(),hud.getWorldWidth(), hud.getWorldHeight());
	}
}