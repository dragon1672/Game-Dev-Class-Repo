#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"
#include "SingleKeyManager.h"
#include "GameEntity.h"
#include "TurretTargetLogic.h"

#include "DynamicPosition.h"
#include "FireLogic.h"

class GameSpace;
class Bullet;

class Turret : GameEntity {
private:
	float timeSinceLastShot;
protected:
	DynamicPosition *myPos;
	DynamicPosition *target;
	FireLogic *myFireLogic;
	GameSpace *space;
	Vector2D direction;

	virtual Shape *getStyle();

	Vector2D tipOfTurret();//could be on child level, but it is used a lot
	void pointToTarget();
	void shoot(Bullet *toShoot);//passes bullet to world to be shot
public:
	static Core::RGB defaultTurretColor;
	static Shape defaultBulletStyle;
	static float defaultBulletSpeed;

	Turret() { timeSinceLastShot = 0; }

	void init(GameSpace *myWorld, DynamicPosition *location, DynamicPosition *target, FireLogic* logic);
	void setFireLogic(FireLogic *toSet);
	void setTarget(DynamicPosition * toSet);
	void changePos(DynamicPosition * toSet);
	void update(float dt);
	void draw(Core::Graphics& graphics);
	virtual void  fireBullet()=0;//should create bullet and call shoot
	virtual float getFireSpeed()=0;//time between Bullets
};

#endif