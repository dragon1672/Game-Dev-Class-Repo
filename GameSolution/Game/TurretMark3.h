#pragma once
#ifndef TURRET_MARK3_H
#define TURRET_MARK3_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark3 : public Turret {
private:
	Shape *getStyle();
public:
	void fireBullet();
	float getFireSpeed();
	float getBulletPower();
};

#endif