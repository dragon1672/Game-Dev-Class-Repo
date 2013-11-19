#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER

#include <vector>
#include "Bullet.h"
#include "Core.h"

class GameSpace;
class Boundary;
/*
  * holds an array of bullet pointers (bullet memory should be handled in the turret
  * should be the only one calling shutdown on bullets
  * should check if bullets are out of bounds
  * bullets that are no longer active will be removed from the bullet list and will be required to be re-added once they are initilized again (active=true)
//*/
class BulletManager {
	Boundary *bounds;
	GameSpace *space;
	std::vector<Bullet *> bullets;
public:
	void init(GameSpace *space, Boundary *bounds);
	Bullet getBullet(int id);
	int    numOfBullets();
	void   addBullet(Bullet *toAdd);

	void setBounds(Boundary *toSet);

	//will delete sequential bullets out of bounds
	void cleanOutOfBoundBullets(int startingIndex);
	
	void update(float dt);
	void draw(Core::Graphics graphics);
};

#endif