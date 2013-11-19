#pragma once
#ifndef TURRET_MARK5_H
#define TURRET_MARK5_H

#include "SingleKeyManager.h"
#include "Turret.h"
#include "BasicBullet.h"

#define MAX_TURRET_MARK5_BULLETS 100

class TurretMark5 : public Turret {
private:
	BasicBullet myBullets[MAX_TURRET_MARK5_BULLETS];
	static float timeBetweenShots;
	float sinceLastShot;
	Shape *getStyle();
	inline int getMaxBullets() const {
		return MAX_TURRET_MARK5_BULLETS;
	}
	inline Bullet* startOfArray() {
		return &myBullets[0];
	}
	void initBullet(int id);
public:
	TurretMark5() { sinceLastShot = 0; }
	void update(float dt);
};

#endif