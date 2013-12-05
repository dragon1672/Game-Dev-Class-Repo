#include "GameSpace.h"

#include "GameMacros.h"
#include "MyRandom.h"
#include "AutoProfileManager.h"
#include "MyGraphics.h"

const int NUMBER_OF_RANDOM_LERP_POINTS = 7; 
const float GameSpace::WORLD_DRAG = 100;

ExplosionEffect basicBoom;

GameSpace::GameSpace() { ; }
GameSpace::GameSpace(float width, float height, const Vector2D& pos, DynamicPosition *mousePos, ScoreManager * manager) {
	init(width, height, pos, mousePos,manager);
}
void       GameSpace::initObjects() {
	LOG(Info,"Initilizing Game Space Objects",1);
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
	enemySpawner.init(this,&myShip);
}
void       GameSpace::init(float width, float height, const Vector2D& pos, DynamicPosition *mousePos, ScoreManager * manager) {
	LOG(Info,"Game Space Init",0);
	this->mousePointer = mousePos;
	this->scoreBoard = manager;
	//init Shape
	min = pos;
	max = pos+Vector2D(width,height);
	initObjects();
	Vector2D one   = min;
	Vector2D two   = pos+Vector2D(width,0);
	Vector2D three = max;
	Vector2D four  = pos+Vector2D(0,height);
	LOG(Info,"Creating Game Style",1);
	gameStyle.initialize(defaultColor, Matrix3D(), 4, one,two,three,four);
}
void       GameSpace::registerBoundary(Boundary *bounds) {
	boundary = bounds;
}
void       GameSpace::drawHealthBar(MyGraphics& graphics, LivingGameEntity *target) {
	float offsetFromTarget = 5;
	float targetSize = target->getStyle()->getRadius();
	Vector2D posOfHealthBar = target->getPos() + Vector2D(-targetSize/2,-(targetSize+offsetFromTarget));//centers x and offsets y
	graphics.drawLoadingBar(posOfHealthBar,target->getHealthPercent(),50,7);
}
//core
bool       GameSpace::update(float dt) {
	PROFILE("Enemy Update");
		enemySpawner.update(dt);
	END_PROFILE;
	PROFILE("Entities Update");
		for(uint i=0;i<myEntities.size();i++) {
			myEntities[i]->update(dt);
		}
	END_PROFILE;
	PROFILE("All partical Update");
		allMyParticals.update(dt);
	END_PROFILE;
	PROFILE("All partical Update");
		myBullets.update(dt);
	END_PROFILE;
	PROFILE("All Entity to Entity collision Update");
		checkEntityEntityCollision();
	END_PROFILE;
	if(enemySpawner.hasBeenDefeated() || myShip.getHealth()<=0) {
		playerHasWon = myShip.getHealth()>0;
		return true;
	}
	return false;
}
void       GameSpace::draw(MyGraphics& graphics) {
	gameStyle.draw(graphics);
	boundary->draw(graphics);
	PROFILE("draw score");
	scoreBoard->draw(graphics,getMin(),2,RGB(255,255,0));
	END_PROFILE;
	PROFILE("draw bullets");
	myBullets.draw(graphics);
	END_PROFILE;
	PROFILE("draw particals");
	allMyParticals.draw(graphics);
	END_PROFILE;
	PROFILE("draw all entities");
	for(uint i=0;i<myEntities.size();i++) {
		myEntities[i]->draw(graphics);
		drawHealthBar(graphics,myEntities[i]);
	}
	END_PROFILE;
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
	LOG(Info,"Entity Added To World",1);
	myEntities.push_back(toAdd);
}
Vector2D   GameSpace::randomWorldPoint() {
	return Vector2D(Random::randomFloat(min.getX(),max.getX()), Random::randomFloat(min.getY(),max.getY()));
}
Vector2D   GameSpace::randomOutOfBoundWorldPoint() {
	float width  = (getMax() - getMin()).getX();
	float height = (getMax() - getMin()).getY();
	float radius = (width>height)? width : height;
	Vector2D offset;
	if(Random::randomBool())
		return getCenter() + Vector2D(Random::randomSign() * Random::randomFloat(radius,2*radius),Random::randomSign() * Random::randomFloat(0,height/2));
	else
		return getCenter() + Vector2D(Random::randomSign() * Random::randomFloat(0,width/2),Random::randomSign() * Random::randomFloat(radius,2*radius));
}
Vector2D   GameSpace::getCenter() {
	float width  = max.getX() - min.getX();
	float height = max.getY() - min.getY();
	return Vector2D(min.getX()+width/2, min.getY()+height/2);
}
DynamicPosition *GameSpace::getMouse() {
	return mousePointer;
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
		addExplosion(myEntities[id]->getPos(),50);
		scoreBoard->LivingEntityDeath(myEntities[id]);
		myEntities.erase(myEntities.begin() + id);
		return true;
	}
	return false;
}
void GameSpace::checkEntityEntityCollision() {
	float SHIP_DAMAGE = 3;
	for(uint i=0;i<myEntities.size();i++) {
		int oppositeTeam = TeamInfo::NO_TEAM;// = myEntities[i]->getTeam();
		if(myEntities[i]->getTeam()==TeamInfo::FRIENLY_TEAM) oppositeTeam = TeamInfo::ENEMY_TEAM;
		if(myEntities[i]->getTeam()==TeamInfo::ENEMY_TEAM) oppositeTeam = TeamInfo::FRIENLY_TEAM;
		int temp = getLivingEntityCollidedWithOfTeam(*myEntities[i]->getStyle(),myEntities[i]->getPos(),oppositeTeam);
		if(temp!=NO_INDEX && (unsigned)temp!=i) {
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