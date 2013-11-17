#pragma once
#ifndef BASIC_TURRET_H
#define BASIC_TURRET_H

#include "SingleKeyManager.h"
#include "Turret.h"

class BasicTurret : public Turret {
private:
	Shape *getStyle();
public:
	void update(float dt);
};

#endif