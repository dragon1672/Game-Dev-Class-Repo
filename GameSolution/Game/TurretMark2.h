#pragma once
#ifndef TURRET_MARK2_H
#define TURRET_MARK2_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark2 : public Turret {
private:
	static float timeBetweenShots;
	float simeSinceLastShot;
	Shape *getStyle();
public:
	void update(float dt, const Vector2D& pos);
};

#endif