#pragma once
#ifndef FIRE_ON_CLICK_H
#define FIRE_ON_CLICK_H

#include "FireLogic.h"

class FireOnClick : public FireLogic {
private:
	int key;
public:
	FireOnClick() { ; }
	FireOnClick(int key) {
		setKey(key);
	}
	void setKey(int toSet);
	bool fired();
};

#endif