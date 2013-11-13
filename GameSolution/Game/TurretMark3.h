#pragma once
#ifndef TURRET_MARK3_H
#define TURRET_MARK3_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark3 : public Turret {
private:
	static float timeBetweenShots;
	float sinceLastShot;
	Shape *getStyle();
public:
	TurretMark3() { sinceLastShot = 0; }
	void update(float dt, const Vector2D& pos);
};

#endif