#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"
#include "SingleKeyManager.h"

class GameSpace;
class Bullet;

class Turret {
protected:
	SingleKeyManager MOUSE;
	Vector2D direction;
	GameSpace *space;
	void shoot(Bullet *toShoot);
	virtual Shape *getStyle();
	void pointToMouse(const Vector2D& pos);
	Vector2D tipOfTurret();
public:
	static Core::RGB defaultTurretColor;
	static Shape defaultBulletStyle;
	static float defaultBulletSpeed;
	Turret() : MOUSE(Core::Input::BUTTON_LEFT) { ; }
	void init(GameSpace *myWorld);
	virtual void update(float dt, const Vector2D& pos);
	void draw(Core::Graphics& graphics, const Vector2D& pos);
};

#endif