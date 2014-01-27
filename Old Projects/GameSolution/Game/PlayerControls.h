#pragma once
#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H

#include "Core.h"

class PlayerControls {
public:
	static const int    minTypeSafeChar = 33;
	static const int    maxTypeSafeChar = 126;
	static const char   accelerate    = 'W';
	static const char   decelerate    = 'S';
	static const char   rotateLeft    = 'A';
	static const char   rotateRight   = 'D';
	static const int    brake         = Core::Input::BUTTON_SHIFT;
	static const int    shoot         = Core::Input::BUTTON_LEFT;
	static const int    boxColision   = 'X';
	static const int    boundColision = 'C';
	static const int    pauseGame     = 'P';
	static const int    warpColision  = 'Z';//press and hold
	//turrets are number keys... >.> not sure how to print that nicely

	const char* getStringFor(int input) const {
		char *ret = "?";//has to be one char long because of how I'm printing type safe chars
		if(minTypeSafeChar <= input && input <= maxTypeSafeChar) {
			ret[0] = (char)input;
		} else {
			switch(input) {
			case Core::Input::KEY_LEFT:
				ret = "Left Arrow Key";
				break;
			case Core::Input::KEY_RIGHT:
				ret = "Right Arrow Key";
				break;
			case Core::Input::KEY_UP:
				ret = "Up Arrow Key";
				break;
			case Core::Input::KEY_DOWN:
				ret = "Down Arrow Key";
				break;
			case Core::Input::KEY_ESCAPE:
				ret = "Esc";
				break;
			case Core::Input::BUTTON_LEFT:
				ret = "Left Mouse Button";
				break;
			case Core::Input::BUTTON_RIGHT:
				ret = "Right Mouse Button";
				break;
			case Core::Input::BUTTON_SHIFT:
				ret = "Shift";
				break;
			}
		}
		return ret;
	}
};

#endif