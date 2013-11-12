#pragma once

#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
//temp
#include "SolarSystem.h"
#include "Turret.h"
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
	
	Turret myTurret;

	Vector2D vel;
	Vector2D pos;
	GameSpace *space;
	float angle;

	float getMinX();
	float getMinY();
	float getMaxX();
	float getMaxY();

	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1,float force=brakePower);

	//update functions
	void  manageAcc(float dt);
	void  manageRot(float dt);
	void  move(float dt);
	float mouseDistanceFromTurretLine();
	bool  mouseWithinTurretRange();
	void  updateTurret();
	void  resetTurret();
public:
	void init(float x, float y, GameSpace *space);
	void addAcc(const Vector2D& toAdd, float scalar=1);
	void draw(Core::Graphics& graphics);
	void update(float dt);
	Matrix3D getShipMatrix();
};