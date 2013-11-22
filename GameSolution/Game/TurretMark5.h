#pragma once
#ifndef TURRET_MARK5_H
#define TURRET_MARK5_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark5 : public Turret {
private:
	Shape *getStyle();
public:
	void fireBullet();
	float getFireSpeed();
	float getBulletPower();
};

#endif