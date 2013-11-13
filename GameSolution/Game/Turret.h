#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"
#include "SingleKeyManager.h"

class GameSpace;
struct Bullet;

class Turret {
protected:
	SingleKeyManager MOUSE;
	Vector2D direction;
	GameSpace *space;
	void shoot(Bullet *toShoot);
	virtual Shape *getStyle()=0;
	void pointToMouse(const Vector2D& pos);
public:
	static Core::RGB defaultTurretColor;
	Turret() : MOUSE(Core::Input::BUTTON_LEFT) { ; }
	void init(GameSpace *myWorld);
	virtual void update(float dt, const Vector2D& pos)=0;
	void draw(Core::Graphics& graphics, const Vector2D& pos);
};

#endif