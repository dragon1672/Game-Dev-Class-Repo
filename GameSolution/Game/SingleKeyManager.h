#pragma once
#ifndef SINGLE_KEY_MANAGER_H
#define SINGLE_KEY_MANAGER_H

#include "Core.h"

class SingleKeyManager {
	int   toCheck;
	int   framesClicked;
	float secondsClicked;
public:
	SingleKeyManager(int toCheck) {
		this->toCheck = toCheck;
	}
	inline void  update(float dt) {
		if(Core::Input::IsPressed( toCheck )) {
			framesClicked++;
			secondsClicked += dt;
		} else {
			framesClicked  = 0;
			secondsClicked = 0;
		}
	}
	inline bool  hasBeenClicked() {
		return (framesClicked==1);
	}
	inline int   getFramesClicked() {
		return framesClicked;
	}
	inline float getSecondsClicked() {
		return secondsClicked;
	}
	inline int   getCheckedElement() {
		return toCheck;
	}
};

#endif