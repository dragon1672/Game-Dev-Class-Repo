#include "GameSpace.h"
#include "MyRandom.h"

const int NUMBER_OF_RANDOM_LERP_POINTS = 7; 

ExplosionEffect basicBoom;

GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, const Vector2D& pos, Core::RGB color) {
	makeGameSpace(color, width, height, pos);
}
void      GameSpace::initObjects() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	myShip.init(min.getX()+(width/2),min.getY()+(height/2),this);
	myBullets.init(this);
	myLerp.init();
	for(int i=0;i<NUMBER_OF_RANDOM_LERP_POINTS;i++) {
		myLerp.addPoint(randomWorldPoint());
	}
}
void      GameSpace::makeGameSpace(Core::RGB color, float width, float height, Vector2D pos) {
	//init Shape
	min = pos+Vector2D(0,0);
	max = pos+Vector2D(width,height);
	initObjects();
	Vector2D one   = min;
	Vector2D two   = pos+Vector2D(width,0);
	Vector2D three = max;
	Vector2D four  = pos+Vector2D(0,height);
	toDraw.initialize(color, Matrix3D(), 4, one,two,three,four);
}
void      GameSpace::registerBoundary(Boundary *bounds) {
	boundary = bounds;
}
void      GameSpace::draw(Core::Graphics& graphics) {
	toDraw.draw(graphics);
	boundary->draw(graphics);
	myShip.draw(graphics);
	myLerp.draw(graphics);
	myBullets.draw(graphics);
	allMyParticals.draw(graphics);
}
void      GameSpace::update(float dt) {
	allMyParticals.update(dt);
	myShip.update(dt);
	myLerp.update(dt);
	myBullets.update(dt);
}
Boundary *GameSpace::getBoundary() { return boundary; }
Vector2D  GameSpace::getMin() { return min; }
Vector2D  GameSpace::getMax() { return max; }
Vector2D  GameSpace::collideVector(const Vector2D& pos, const Vector2D& vel) {
	return boundary->collideVector(pos,vel);
}
void      GameSpace::addEffect(int size, ParticalEffect* toAdd) {
	allMyParticals.newEffect(size,toAdd);
}
void      GameSpace::addBullet(Bullet *toAdd) {
	myBullets.addBullet(toAdd);
}
void      GameSpace::addExplosion(const Vector2D& pos, int size, float lifetime) {
	basicBoom.init(lifetime,pos);
	allMyParticals.newEffect(size, &basicBoom);
}
Vector2D  GameSpace::randomWorldPoint() {
	return Vector2D(Random::randomFloat(min.getX(),max.getX()), Random::randomFloat(min.getY(),max.getY()));
}
Vector2D  GameSpace::getCenter() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	return Vector2D(min.getX()+width/2, min.getY()+height/2);
}