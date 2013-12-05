#pragma once
#ifndef PARTICAL_MANAGER_H
#define PARTICAL_MANAGER_H

#include "Partical.h"
#include "ParticalEffect.h"

class ParticalManager {
public:
	static const int MAX_PARTICALS = 5000;
	void newEffect(int size, ParticalEffect *effect);
	void update(float dt);
	void draw(MyGraphics& graphics);
private:
	Partical particals[MAX_PARTICALS];
};

#endif