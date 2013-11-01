/*#ifndef SPACE_SHIP
#define SPACE_SHIP

#include "Core.h"
#include "Vector 2.h"
#include "GameObject.h"
#include "GameSpace.h"

class Spaceship : public GameObject {
	static Core::RGB shipColor;
	static Shape thisShape;
	Vector2D vel;
	static const float brakePower;
	
	float getMinX();
	float getMinY();
	float getMaxX();
	float getMaxY();
	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1);
	void move();
public:
	Vector2D pos;
	void init(float x, float y, GameSpace *space);
	virtual void draw(Core::Graphics graphics);
	void addAcc(Vector2D toAdd,float scalar=1);
	void update(float dt);
};



#endif//*/
#pragma once

#include "Vector 2.h"
#include "Core.h"
#include "GameObject.h"
//class Shape;
class GameSpace;


class Spaceship {
	Vector2D again;
	static Core::RGB shipColor;
	static const float brakePower;
	static Shape thisShape;
	Vector2D vel;
	Vector2D pos;
	GameSpace *space;
	float getMinX();
	float getMinY();
	float getMaxX();
	float getMaxY();

	void bounce();
	void warp();
	void collide();
	void brake(float scalar=1);
public:
	void init(float x, float y, GameSpace *space);
	void addAcc(Vector2D toAdd, float scalar=1);
	//using GameObject::draw;
	void draw(Core::Graphics graphics);
	//using GameObject::update;
	void update(float dt);


};