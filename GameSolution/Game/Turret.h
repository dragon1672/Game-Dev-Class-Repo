#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"
#include "SingleKeyManager.h"
#include "GameEntity.h"

class GameSpace;
class Bullet;

class Turret : GameEntity {
protected:
	GameEntity *parent;
	GameSpace *space;
	SingleKeyManager MOUSE;
	Vector2D direction;
	virtual Shape *getStyle();
	virtual int getMaxBullets() const;
	virtual Bullet* startOfArray();
	virtual void initBullet(int id);

	//provides a basic tool for singleShot
	bool shoot();

	Vector2D getParentPos();

	//passes bullet to be added to world
	void shootBullet(Bullet *toShoot);
	void pointToMouse();
	Vector2D tipOfTurret();
public:
	static Core::RGB defaultTurretColor;
	static float defaultBulletSpeed;

	Turret() : MOUSE(Core::Input::BUTTON_LEFT) { ; }
	void init(GameSpace *myWorld, GameEntity *parent);
	virtual void update(float dt);
	void draw(Core::Graphics& graphics);
};

#endif