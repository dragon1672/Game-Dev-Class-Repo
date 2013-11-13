#pragma once
#ifndef TURRET_MARK5_H
#define TURRET_MARK5_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark5 : public Turret {
private:
	static float timeBetweenShots;
	float sinceLastShot;
	Shape *getStyle();
public:
	TurretMark5() { sinceLastShot = 0; }
	void update(float dt, const Vector2D& pos);
};

#endif