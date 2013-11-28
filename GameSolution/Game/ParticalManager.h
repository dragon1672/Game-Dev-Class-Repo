#pragma once
#ifndef PARTICAL_MANAGER_H
#define PARTICAL_MANAGER_H

#include "GameGlobal.h"

#include "Partical.h"
#include "ParticalEffect.h"

#define MAX_PARTICALS 5000

class ParticalManager {
private:
	Partical particals[MAX_PARTICALS];
public:
	void newEffect(int size, ParticalEffect *effect);
	void update(float dt);
	void draw(MyGraphics& graphics);
};

#endif