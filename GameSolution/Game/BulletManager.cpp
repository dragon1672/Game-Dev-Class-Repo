#include "BulletManager.h"


Shape temp(RGB(255,0,255), 5,
	10*Vector2D(   .7f, -1.0f ),
	10*Vector2D(  0.0f,  1.0f ),
	10*Vector2D(  -.6f, -1.0f ),
	10*Vector2D(  1.0f,   .25f),
	10*Vector2D( -1.0f,   .25f) );

void   BulletManager::init(Boundary *bounds) {
	this->bounds = bounds;
}
Bullet BulletManager::getBullet(int id) {
	return bullets[id];
}
int    BulletManager::numOfBullets() {
	return bullets.size();
}
void   BulletManager::addBullet(Bullet *toAdd) {
	bullets.push_back(*toAdd);//copys information
}
void   BulletManager::setBounds(Boundary *toSet) {
	bounds = toSet;
}
//will delete sequential bullets out of bounds
void   BulletManager::cleanOutOfBoundBullets(int startingIndex) {
	if(bounds->hasCollided(bullets[startingIndex].pos)) {
		bullets.erase(bullets.begin() + startingIndex);
		if((unsigned)startingIndex<bullets.size()) cleanOutOfBoundBullets(startingIndex);//incase multiple in a row
	}
}
void   BulletManager::update(float dt) {
	for(unsigned int i=0;i<bullets.size();i++) {
		bullets[i].update(dt);
		cleanOutOfBoundBullets(i);
	}
}
void   BulletManager::draw(Core::Graphics graphics) {
	for(unsigned int i=0;i<bullets.size();i++) {
		bullets[i].draw(graphics);
	}
}