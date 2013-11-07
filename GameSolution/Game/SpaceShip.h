#pragma once

#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"
class GameSpace;


class Spaceship {
	static Core::RGB shipColor;
	static const float brakePower;
	static Shape thisShape;
	static float TURRET_LENGTH;

	Vector2D vel;
	Vector2D pos;
	GameSpace *space;
	Vector2D turret;
	float angle;

	float getMinX();
	float getMinY();
	float getMaxX();
	float getMaxY();

	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1);

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
	void addAcc(Vector2D toAdd, float scalar=1);
	void draw(Core::Graphics graphics);
	void update(float dt);
};