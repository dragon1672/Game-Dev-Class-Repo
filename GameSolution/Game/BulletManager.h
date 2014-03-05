#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER

#include <vector>
#include "Bullet.h"
#include "Core.h"

class GameSpace;
class Boundary;

class BulletManager {
	GameSpace *space;
	std::vector<Bullet> bullets;
public:
	void init(GameSpace *space);
	Bullet getBullet(int id);
	int    numOfBullets();
	void   addBullet(Bullet *toAdd);

	//will delete sequential bullets out of bounds
	bool cleanOutOfBoundBullet(int index);
	
	void update(float dt);
	void draw(MyGraphics& graphics);
};

#endif