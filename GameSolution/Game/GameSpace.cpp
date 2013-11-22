#include "GameSpace.h"
#include "MyRandom.h"

const int NUMBER_OF_RANDOM_LERP_POINTS = 7; 
const float GameSpace::WORLD_DRAG = 100;

ExplosionEffect basicBoom;

GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, const Vector2D& pos, Core::RGB color) {
	init(width, height, pos, color);
}
void       GameSpace::initObjects() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	myShip.init(min.getX()+(width/2),min.getY()+(height/2),this);
	myBullets.init(this);
	myLerp.init();
	for(int i=0;i<NUMBER_OF_RANDOM_LERP_POINTS;i++) {
		myLerp.addPoint(randomWorldPoint());
	}
	addLivingEntity(&myShip);
	addLivingEntity(&myLerp);
}
void       GameSpace::init(float width, float height, const Vector2D& pos, Core::RGB color) {
	//init Shape
	min = pos+Vector2D(0,0);
	max = pos+Vector2D(width,height);
	initObjects();
	Vector2D one   = min;
	Vector2D two   = pos+Vector2D(width,0);
	Vector2D three = max;
	Vector2D four  = pos+Vector2D(0,height);
	gameStyle.initialize(color, Matrix3D(), 4, one,two,three,four);
}
void       GameSpace::registerBoundary(Boundary *bounds) {
	boundary = bounds;
}
void       GameSpace::drawHealthBar(Core::Graphics& graphics, LivingGameEntity *target) {
	float offsetFromTarget = 5;
	float targetSize = target->getStyle()->getRadius();
	Vector2D posOfHealthBar = target->getPos() + Vector2D(-targetSize/2,-(targetSize+offsetFromTarget));//centers x and offsets y
	ExtendedGraphics::drawLoadingBar(graphics,posOfHealthBar,target->getHealthPercent(),50,5);
}
//core
void       GameSpace::update(float dt) {
	for(uint i=0;i<myEntities.size();i++) {
		myEntities[i]->update(dt);
	}
	allMyParticals.update(dt);
	myBullets.update(dt);
	checkEntityEntityCollision();
}
void       GameSpace::draw(Core::Graphics& graphics) {
	gameStyle.draw(graphics);
	boundary->draw(graphics);
	myBullets.draw(graphics);
	allMyParticals.draw(graphics);
	for(uint i=0;i<myEntities.size();i++) {
		myEntities[i]->draw(graphics);
		drawHealthBar(graphics,myEntities[i]);
	}
}

Boundary  *GameSpace::getBoundary() { return boundary; }
Vector2D   GameSpace::getMin() { return min; }
Vector2D   GameSpace::getMax() { return max; }
HitInfo    GameSpace::collideVector(const Vector2D& pos, const Vector2D& vel) {
	return boundary->collideVector(pos,vel);
}
void       GameSpace::addEffect(int size, ParticalEffect* toAdd) {
	allMyParticals.newEffect(size,toAdd);
}
void       GameSpace::addBullet(Bullet *toAdd) {
	myBullets.addBullet(toAdd);
}
void       GameSpace::addExplosion(const Vector2D& pos, int size, float lifetime) {
	basicBoom.init(lifetime,pos);
	allMyParticals.newEffect(size, &basicBoom);
}
void       GameSpace::addLivingEntity(LivingGameEntity *toAdd) {
	myEntities.push_back(toAdd);
}
Vector2D   GameSpace::randomWorldPoint() {
	return Vector2D(Random::randomFloat(min.getX(),max.getX()), Random::randomFloat(min.getY(),max.getY()));
}
Vector2D   GameSpace::getCenter() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	return Vector2D(min.getX()+width/2, min.getY()+height/2);
}

LivingGameEntity* GameSpace::getLivingEntity(int id) {
	return myEntities[id];
}
void GameSpace::cleanUpAllLivingEntities() {
	for(uint i=0;i<myEntities.size();i++) {
		if(cleanUpEntity(i))
			i--;
		//because the array size will be shortened by one offsetting 'i'
	}
}
bool GameSpace::cleanUpEntity(int id) {
	if(myEntities[id]->getHealth()<=0) {
		addExplosion(myEntities[id]->getPos(),10);
		myEntities.erase(myEntities.begin() + id);
		return true;
	}
	return false;
}
void GameSpace::checkEntityEntityCollision() {
	float SHIP_DAMAGE = 3;
	for(uint i=0;i<myEntities.size();i++) {
		int oppositeTeam = NO_TEAM;// = myEntities[i]->getTeam();
		if(myEntities[i]->getTeam()==FRIENLY_TEAM) oppositeTeam = ENEMY_TEAM;
		if(myEntities[i]->getTeam()==ENEMY_TEAM) oppositeTeam = FRIENLY_TEAM;
		int temp = getLivingEntityCollidedWithOfTeam(*myEntities[i]->getStyle(),myEntities[i]->getPos(),oppositeTeam);
		if(temp!=NO_INDEX && temp!=i) {
			myEntities[i]->removeHP(SHIP_DAMAGE);
			if(cleanUpEntity(i)) i--;
		}
	}
}
//that do not match team
int GameSpace::getLivingEntityClosest(const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	Vector2D shortestDistance;//will have a length of 0
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		Vector2D temp = pos-myEntities[i]->getPos();
		if(temp.lengthSquared()<shortestDistance.lengthSquared()) {
			if(myEntities[i]->getTeam()!=team) {
				shortestDistance = temp;
				ret = i;
			}
		}
	}
	return ret;
}
int GameSpace::getLivingEntityCollidedWith(const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		if(myEntities[i]->getStyle()->collision(pos,myEntities[i]->getPos())) {
			if(myEntities[i]->getTeam()!=team) {
				ret = i;
			}
		}
	}
	return ret;
}
int GameSpace::getLivingEntityCollidedWith(const Shape& toCheck, const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		if(myEntities[i]->getStyle()->collision(toCheck,myEntities[i]->getPos(),pos)) {
			if(myEntities[i]->getTeam()!=team) {
				ret = i;
			}
		}
	}
	return ret;
}
//that match team
int GameSpace::getLivingEntityClosestOfTeam(const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	Vector2D shortestDistance;//will have a length of 0
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		Vector2D temp = pos-myEntities[i]->getPos();
		if(temp.lengthSquared()<shortestDistance.lengthSquared()) {
			if(myEntities[i]->getTeam()==team) {
				shortestDistance = temp;
				ret = i;
			}
		}
	}
	return ret;
}
int GameSpace::getLivingEntityCollidedWithOfTeam(const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		if(myEntities[i]->getStyle()->collision(pos,myEntities[i]->getPos())) {
			if(myEntities[i]->getTeam()==team) {
				ret = i;
			}
		}
	}
	return ret;
}
int GameSpace::getLivingEntityCollidedWithOfTeam(const Shape& toCheck, const Vector2D& pos, int team, int startingIndex) {
	int ret = NO_INDEX;
	for(uint i=startingIndex;i<myEntities.size() && ret==NO_INDEX;i++) {
		if(myEntities[i]->getStyle()->collision(toCheck,myEntities[i]->getPos(),pos)) {
			if(myEntities[i]->getTeam()==team) {
				ret = i;
			}
		}
	}
	return ret;
}