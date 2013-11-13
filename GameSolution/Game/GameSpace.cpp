#include "GameSpace.h"
#include "MyRandom.h"
GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, const Vector2D& pos, Core::RGB color) {
	makeGameSpace(color, width, height, pos);
}
void      GameSpace::initObjects() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	myShip.init(min.getX()+(width/2),min.getY()+(height/2),this);


	myLerp.init();
	//lerper get 7 random points
	for(int i=0;i<7;i++) {
		myLerp.addPoint(randomWorldPoint());
	}
}
void      GameSpace::makeGameSpace(Core::RGB color, float width, float height, Vector2D pos) {
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
	//hasBounds = true;
	boundary = bounds;
}
void      GameSpace::draw(Core::Graphics& graphics) {
	toDraw.draw(graphics);
	boundary->draw(graphics);
	myShip.draw(graphics);
	myLerp.draw(graphics);
	myBullets.draw(graphics);
}
bool      GameSpace::update(float dt) {
	if(Core::Input::IsPressed( Core::Input::KEY_ESCAPE   )) return true;
	myShip.update(dt);
	myLerp.update(dt);
	myBullets.update(dt);
	myBullets.setBounds(boundary);
	return false;
}
Boundary *GameSpace::getBoundary() { return boundary; }
Vector2D  GameSpace::getMin() { return min; }
Vector2D  GameSpace::getMax() { return max; }
Vector2D  GameSpace::collideVector(const Vector2D& pos, const Vector2D& vel) {
	//if(hasBounds) {
		return boundary->collideVector(pos,vel);
	/*not my job if they don't include a boundary
	} else {
		if(pos.getX() < min.getX() || pos.getX() > max.getX()) return Vector2D(-vel.getX(), vel.getY());
		if(pos.getY() < min.getY() || pos.getY() > max.getY()) return Vector2D( vel.getX(),-vel.getY());
		return vel;
	}//*/
}
void      GameSpace::addBullet(Bullet *toAdd) {
	myBullets.addBullet(toAdd);
}
Vector2D  GameSpace::randomWorldPoint() {
	return Vector2D(Random::randomFloat(min.getX(),max.getX()), Random::randomFloat(min.getY(),max.getY()));
}
Vector2D  GameSpace::getCenter() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	return Vector2D(min.getX()+width/2, min.getY()+height/2);
}