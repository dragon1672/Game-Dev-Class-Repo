#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

//interfaces and inheritance
#include "LivingGameEntity.h"

//core
#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
#include "Timer.h"//currently for unlocking turret

#include "ExhaustEffect.h"

#include "Turret.h"
#include "BasicTurret.h"
#include "TurretMark2.h"
#include "TurretMark3.h"
#include "TurretMark4.h"
#include "TurretMark5.h"

//logics
#include "FireOnClick.h"
#include "TargetMouse.h"
#include "UserMoveLogic.h"

class GameSpace;

//#define DEBUG_SPACESHIP
#define NUM_OF_TURRETS 5


class Spaceship : public LivingGameEntity {
	static const float SHIP_FULL_STARTING_HEALTH;
	static Core::RGB shipColor;
	static const float brakePower;
	static Shape thisShape;
	static float TURRET_LENGTH;
	static float ACC;
	static float rotationAcc;
	static float maxSpeed;
	
	//firing logic for player
	FireOnClick myFiringLogic;
	UserMoveLogic myMovementLogic;

	Timer turretTimer;

	Turret *turrets[NUM_OF_TURRETS];
	//these are manually placed in the array
	BasicTurret myBasicTurret;//1
	TurretMark2 myMark2Turret;//2
	TurretMark3 myMark3Turret;//3
	TurretMark4 myMark4Turret;//4
	TurretMark5 myMark5Turret;//5
	int maxAccessibleTurret;
	Turret *currentTurret;
	GameSpace *space;
	ExhaustEffect myEffect;

	//movement
	Vector2D vel;
	Vector2D pos;
	Matrix3D rotationMatrix;

	void warp();
	void collide(float dt);
	void brake(float scalar=1,float force=brakePower);

	//update functions
	void  updateSelectedTurret();
	void  unlockTurret();//will enable the next Turret
	void  manageAcc(float dt);
	void  manageRot(float dt);
	void  move(float dt);
public:
	void     init(float x, float y, GameSpace *space);
	void     addAcc(const Vector2D& toAdd, float scalar=1);
	Shape*   getStyle();
	void     draw(MyGraphics& graphics);
	void     update(float dt);
	Matrix3D getTransMatrix();
	Matrix3D getRotationMat();
	Vector2D getPos();
	int getTeam();
};

#endif