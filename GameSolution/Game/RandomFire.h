#pragma once
#ifndef RandomFire_h
#define RandomFire_h

#include "FireLogic.h"

class RandomFire : FireLogic {
private:
	float freq;
public:
	RandomFire(float freq=.1) {
		setFreq(freq);
	}
	void setFreq(float toSet);
	bool fired();
};

#endif