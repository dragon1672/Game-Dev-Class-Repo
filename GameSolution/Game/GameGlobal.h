#pragma once
#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H
//have # defines
//define global constents like angles in a circle
const float anglesInCircle = 2*3.14f;

#define DEBUG_GLOBAL
#ifdef DEBUG_GLOBAL
	//pther debug defines
	#define DEBUG_Controller
	
//functions
#include <sstream>
#include "Vector 2.h"
namespace DEBUG {
	inline std::string num2str(float num) {
		std::stringstream ss;
		ss << num;
		return ss.str();
	}
	inline std::string num2str(int num) {
		std::stringstream ss;
		ss << num;
		return ss.str();
	}
	inline std::string vec2str(const Vector2D& vec) {
		std::stringstream ss;
		ss << vec;
		return ss.str();
	}
}
#endif//DEBUG

#endif