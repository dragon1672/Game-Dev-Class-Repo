#pragma once
#ifndef TURRET_MARK4_H
#define TURRET_MARK4_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark4 : public Turret {
private:
	static float timeBetweenShots;
	float sinceLastShot;
	Shape *getStyle();
public:
	TurretMark4() { sinceLastShot = 0; }
	void update(float dt);
};

#endif