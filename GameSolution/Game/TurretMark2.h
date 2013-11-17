#pragma once
#ifndef TURRET_MARK2_H
#define TURRET_MARK2_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark2 : public Turret {
private:
	static float timeBetweenShots;
	float sinceLastShot;
	Shape *getStyle();
public:
	TurretMark2() { sinceLastShot = 0; }
	void update(float dt);
};

#endif