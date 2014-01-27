#pragma once
#ifndef GAME_DEBUG_DEFINES_H
#define GAME_DEBUG_DEFINES_H

#define DEBUG_GLOBAL
#ifdef DEBUG_GLOBAL
	//other debug defines
	#define DEBUG_Controller
	#define DEBUG_SPACESHIP
	
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