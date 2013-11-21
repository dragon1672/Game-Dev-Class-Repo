#include "BulletManager.h"
#include "Boundary.h"
#include "GameSpace.h"


Shape temp(RGB(255,0,255), 5,
	10*Vector2D(   .7f, -1.0f ),
	10*Vector2D(  0.0f,  1.0f ),
	10*Vector2D(  -.6f, -1.0f ),
	10*Vector2D(  1.0f,   .25f),
	10*Vector2D( -1.0f,   .25f) );

void   BulletManager::init(GameSpace *space) {
	this->space  = space;
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
//will delete sequential bullets out of bounds
void   BulletManager::cleanOutOfBoundBullets(int startingIndex) {
	if(space->getBoundary()->hasCollided(bullets[startingIndex].pos)) {
		space->addExplosion(bullets[startingIndex].pos);
		bullets.erase(bullets.begin() + startingIndex);
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