#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
#include "SolarSystem.h"

#include "Turret.h"
#include "BasicTurret.h"
#include "TurretMark2.h"
class GameSpace;

#define DEBUG_SPACESHIP

class Spaceship {
	static Core::RGB shipColor;
	static const float brakePower;
	static Shape thisShape;
	static float TURRET_LENGTH;
	static float ACC;
	static float rotationAcc;
	static float maxSpeed;

	//temp
	SolarSystem bodyGuards;
	
	//
	Turret *turrets[5];
	BasicTurret *myBasicTurret;
	TurretMark2 *myMark2Turret;
	Turret *currentTurret;
	GameSpace *space;

	//movement
	Vector2D vel;
	Vector2D pos;
	float angle;

	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1,float force=brakePower);

	//update functions
	void  manageAcc(float dt);
	void  manageRot(float dt);
	void  move(float dt);
public:
	void init(float x, float y, GameSpace *space);
	void addAcc(const Vector2D& toAdd, float scalar=1);
	void draw(Core::Graphics& graphics);
	void update(float dt);
	Matrix3D getShipMatrix();
};

#endif