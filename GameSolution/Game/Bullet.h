#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Vector 2.h"
#include "Shape.h"

struct Bullet {
	Vector2D pos;
	Vector2D vel;
	Shape *style;
	int team;
	Bullet
};

#endif