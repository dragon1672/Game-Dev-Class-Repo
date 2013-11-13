#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER

#include <vector>
#include "Bullet.h"
#include "Core.h"
#include "Boundary.h"

class BulletManager {
	Boundary *bounds;
	std::vector<Bullet> bullets;
public:
	void init(Boundary *bounds);
	Bullet getBullet(int id);
	int numOfBullets();
	void addBullet(Bullet *toAdd);
	//will delete sequential bullets out of bounds
	void cleanOutOfBoundBullets(int startingIndex);
	
	void update(float dt);
	void draw(Core::Graphics graphics);
};

#endif