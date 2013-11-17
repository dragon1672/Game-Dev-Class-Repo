#pragma once
#ifndef EXHAUST_EFFECT_H
#define EXHAUST_Effect_H

#include "ParticalEffect.h"

class ExhaustEffect : public ParticalEffect {
public:
	virtual void init(int size, const Vector2D& pos, float lifetime);
	void update(float dt);
	void draw(Core::Graphics graphics);
};

#endif