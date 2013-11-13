#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER

#include <vector>
#include "Bullet.h"
#include "Core.h"
#include "Boundary.h"

class BulletManager {
	float startX;
	float startY;
	float endX;
	float endY;
	std::vector<Bullet> bullets;
public:
	BulletManager() {
		startX = 0;		startY = 0;
		endX   = 0;		endY   = 0;
	}
	Bullet getBullet(int id) {
		return bullets[id];
	}
	int numOfBullets() {
		return bullets.size();
	}
	void addBullet(Bullet *toAdd) {
		bullets.push_back(*toAdd);//copys information
	}
	//will delete sequential bullets out of bounds
	void cleanOutOfBoundBullets(int startingIndex) {
		if(    bullets[startingIndex].pos.getX() > endX
			|| bullets[startingIndex].pos.getY() > endY
			|| bullets[startingIndex].pos.getX() < startX
			|| bullets[startingIndex].pos.getY() < startY) {
				bullets.erase(bullets.begin() + startingIndex);
				cleanOutOfBoundBullets(startingIndex);//incase multiple in a row
		}
	}
	void update(float dt) {
		for(unsigned int i=0;i<bullets.size();i++) {
			Bullet temp = bullets[i];
			if(bounds) cleanOutOfBoundBullets(i);
			bullets[i].pos = bullets[i].pos + bullets[i].vel*dt;
		}
	}
	void draw(Core::Graphics graphics) {
		for(unsigned int i=0;i<bullets.size();i++) {
			Bullet temp = bullets[i];
			temp.style->draw(graphics,temp.pos);
		}
	}
};

#endif