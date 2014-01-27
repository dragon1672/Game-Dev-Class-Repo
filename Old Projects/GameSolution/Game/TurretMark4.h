#pragma once
#ifndef TURRET_MARK4_H
#define TURRET_MARK4_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark4 : public Turret {//the shotgun
private:
	static const int NUM_OF_SHOTS = 7;
	Shape *getStyle();
public:
	void fireBullet();
	float getFireSpeed();
	float getBulletPower();
};

#endif