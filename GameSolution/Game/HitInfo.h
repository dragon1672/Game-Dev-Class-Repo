#pragma once
#ifndef HIT_INFO
#define HIT_INFO

#include "Vector 2.h"

struct HitInfo {
	HitInfo() { 
		hasHit = false;
	}
	HitInfo(const Vector2D& pos, const Vector2D& vel) {
		this->pos = pos;
		this->vel = vel;
		hasHit = false;
	}
	bool hasHit;
	Vector2D pos;
	Vector2D vel;
};

#endif