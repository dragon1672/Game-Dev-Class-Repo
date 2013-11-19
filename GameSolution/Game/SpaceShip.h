#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "GameEntity.h"

#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
#include "SolarSystem.h"

#include "ExhaustEffect.h"

#include "Turret.h"
#include "BasicTurret.h"
#include "TurretMark2.h"
#include "TurretMark3.h"
#include "TurretMark4.h"
#include "TurretMark5.h"
class GameSpace;

//#define DEBUG_SPACESHIP
#define NUM_OF_TURRETS 5


class Spaceship : public GameEntity {
	static Core::RGB shipColor;
	static const float brakePower;
	static Shape thisShape;
	static float TURRET_LENGTH;
	static float ACC;
	static float rotationAcc;
	static float maxSpeed;
	
	//
	Turret *turrets[NUM_OF_TURRETS];
	//these are manually placed in the array
	BasicTurret myBasicTurret;//1
	TurretMark2 myMark2Turret;//2
	TurretMark3 myMark3Turret;//3
	TurretMark4 myMark4Turret;//4
	TurretMark5 myMark5Turret;//5
	Turret *currentTurret;
	GameSpace *space;
	ExhaustEffect myEffect;

	//movement
	Vector2D vel;
	Vector2D pos;
	float angle;

	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1,float force=brakePower);

	//update functions
	void  updateSelectedTurret();
	void  manageAcc(float dt);
	void  manageRot(float dt);
	void  move(float dt);
public:
	void     init(float x, float y, GameSpace *space);
	void     addAcc(const Vector2D& toAdd, float scalar=1);
	Shape*   getStyle();
	void     draw(Core::Graphics& graphics);
	void     update(float dt);
	Matrix3D getTransMatrix();
	Matrix3D getRotationMat();
};

#endif