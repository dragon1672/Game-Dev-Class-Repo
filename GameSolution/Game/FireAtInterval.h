#pragma once
#ifndef FireAtInterval_h
#define FireAtInterval_h

#include "FireLogic.h"

class FireAtInterval : FireLogic {
private:
	float freq;
public:
	FireAtInterval(float freq=2) {
		setFreq(freq);
	}
	void setFreq(float toSet);
	bool fired();
};

#endif