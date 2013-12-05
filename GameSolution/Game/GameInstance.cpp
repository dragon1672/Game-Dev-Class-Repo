#include "GameInstance.h"
#include "MyRandom.h"
#include "ExtendedGraphics.h"
#include "PlayerControls.h"
#include "AutoProfileManager.h"

const int MAX_POINTS = 60; //for generating circle World
const int NORMAL_MAX_POINTS = 10;//generating other worlds


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


GameInstance::GameInstance (int width, int height) : width(width), 
												 height(height), 
												 hud(width,height) {
	LOG(Info,"GameInstance Init Start",0);

	//gamespace
	Vector2D worldOffset = Vector2D(hud.getWorldWidth()/2,hud.getWorldHeight()/2);
	myWorld.init(hud.getWorldWidth(),hud.getWorldHeight(),-worldOffset,&worldMousePos, &scoreKeeper);
	worldOffset = hud.getWorldoffset() + worldOffset;
	gameSpaceGraphic.init(worldOffset,hud.getWorldWidth(),hud.getWorldHeight());
	//mice
	LOG(Info,"Setting Mouse positions and offsets",1);
	mousePos.init(Vector2D(0,0));
	worldMousePos.init(-worldOffset);
	
	//buttons
	LOG(Info,"Starting up Buttons",1);
	ComplexBoundsKey.setToCheck(PlayerControls::boundColision);
	SimpleBoundsKey.setToCheck(PlayerControls::boxColision);
	PauseButton.setToCheck(PlayerControls::pauseGame);
	//bounds
	setDynamicBounds();
	initSimpleBounds();
	currentBounds = &simpleBounds;
	myWorld.registerBoundary(currentBounds);
}
void GameInstance::initSimpleBounds() {
	float startX = myWorld.getMin().getX();
	float startY = myWorld.getMin().getY();
	float endX   = myWorld.getMax().getX();
	float endY   = myWorld.getMax().getY();
	simpleBounds.init(startX,startY,endX,endY);

}
void GameInstance::setStaticBounds() {
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
void GameInstance::setDynamicBounds() {
	Vector2D randomPoly[MAX_POINTS];
	float padding = 5;
	float sizeOfWalls = 5;
	float worldWidth    = hud.getWorldWidth();
	float worldHeight   = hud.getWorldHeight();

	int sides = Random::randomInt(4,NORMAL_MAX_POINTS+2);
	if(sides > NORMAL_MAX_POINTS) sides = MAX_POINTS;//make a circle World
	generateRandomPolygon(randomPoly, sides, sizeOfWalls);//stored in randomPoly
	
	float polyWidth  = 2 * sizeOfWalls;
	float polyHeight = 2 * sizeOfWalls;
	float scaleX = (worldWidth  - 2 * padding) / polyWidth;
	float scaleY = (worldHeight - 2 * padding) / polyHeight;
	Matrix3D scaler = Matrix3D::translate(myWorld.getCenter()+Vector2D(padding,padding)) * Matrix3D::scaleX(scaleX) * Matrix3D::scaleY(scaleY);
		
	complexBounds.init(sides,randomPoly,scaler);

}
void GameInstance::updateCurrentBounds() {
	if(SimpleBoundsKey.hasBeenClicked()) currentBounds = &simpleBounds;
	if(ComplexBoundsKey.hasBeenClicked()) currentBounds = &complexBounds;
}
float tempAngle = 0;
float tempangleAcc = 1;
bool GameInstance::update(float dt) {
	tempAngle += tempangleAcc*dt;
	//gameSpaceGraphic.setGlobalTrans(Matrix3D::rotationMatrix(tempAngle));

	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	PauseButton.update(dt);
	if(PauseButton.hasBeenClicked()) isPaused = !isPaused; //toggle pause
	if(!isPaused) {
		SimpleBoundsKey.update(dt);
		ComplexBoundsKey.update(dt);
		updateCurrentBounds();
		PROFILE("World update");
		myWorld.registerBoundary(currentBounds);
		myWorld.update(dt);
		END_PROFILE;
	}
	return false;
}
Core::RGB GameInstance::getWorldColor() {
	Core::RGB pauseColor = RGB(50,50,50);
	if(isPaused) return pauseColor;
	if(currentBounds == &complexBounds) return RGB(10,10,10);
	if(currentBounds == &simpleBounds)  return RGB(0,0,10); 
	return RGB(0,255,0);//GREEN, it should never been this
}
void GameInstance::draw(MyGraphics& graphics) {
	//update graphic pointers
	myGraphic.setGraphic(&graphics);
	gameSpaceGraphic.setGraphic(&graphics);
	PROFILE("HUD draw");
		hud.paintWorld(myGraphic,getWorldColor());
		hud.draw(myGraphic);
	END_PROFILE;
	PROFILE("World draw");
		myWorld.draw(gameSpaceGraphic);
	END_PROFILE;
	if(isPaused) {
		hud.worldPopup(myGraphic,"GAME HAS BEEN PAUSED",ExtendedGraphics::brightness(getWorldColor(),.5));
	}
}
DynamicPosition *GameInstance::getMouse() {
	return &mousePos;
}
DynamicPosition *GameInstance::getWorldMouse() {
	return &worldMousePos;
}