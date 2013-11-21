#pragma once
#ifndef TURRET_MARK2_H
#define TURRET_MARK2_H

#include "SingleKeyManager.h"
#include "Turret.h"

class TurretMark2 : public Turret {
private:
	Shape *getStyle();
public:
	void fireBullet();
	float getFireSpeed();
};

#endif