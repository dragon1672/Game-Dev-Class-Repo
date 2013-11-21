#pragma once
#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include "ExportHeader.h"

class Vector2D;

class ENGINE_SHARED Random {
public:
	static int      randomInt(int low, int high);
	static float    randomFloat();
	static float    randomFloat(float low, float high);
	static Vector2D randomUnitVector();
	static Vector2D randomFloatVector(float low, float high);
	static Vector2D randomIntVector  (int   low, int   high);
	static void     init();
};

#endif//MY_RANDOM_H
