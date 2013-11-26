#include "BulletManager.h"
#include "Boundary.h"
#include "GameSpace.h"

#include "AutoProfileManager.h"

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
//will delete bullets out of bounds
bool   BulletManager::cleanOutOfBoundBullet(int index) {
	if(space->getBoundary()->hasCollided(bullets[index].pos)
		|| !bullets[index].isActive) {
		space->addExplosion(bullets[index].pos);
		bullets.erase(bullets.begin() + index);
		return true;
	}
	return false;
}
void   BulletManager::update(float dt) {
	PROFILE("Single Bullet Update");
	for(uint i=0;i<bullets.size();i++) {
		bullets[i].update(dt);
		int entityCollidedWith = space->getLivingEntityCollidedWith(*bullets[i].style,bullets[i].pos,bullets[i].team);
		if(entityCollidedWith!=GameSpace::NO_INDEX) {
			space->getLivingEntity(entityCollidedWith)->removeHP(bullets[i].power);
			space->cleanUpEntity(entityCollidedWith);//clean up
			bullets[i].isActive = false;
		}
		if(cleanOutOfBoundBullet(i)) i--;//because this will decrease size of the array by one, which throws off the iterator 'i'
		END_PROFILE;
	}
}
void   BulletManager::draw(Core::Graphics graphics) {
	for(uint i=0;i<bullets.size();i++) {
		PROFILE("Single Bullet Draw");
		bullets[i].draw(graphics);
		END_PROFILE;
	}
}