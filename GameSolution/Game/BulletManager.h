#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER

#include <vector>
#include "Bullet.h"
#include "Core.h"

class GameSpace;
class Boundary;

class BulletManager {
	Boundary *bounds;
	GameSpace *space;
	std::vector<Bullet> bullets;
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