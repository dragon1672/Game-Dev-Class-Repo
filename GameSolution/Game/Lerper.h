#pragma once
#ifndef LERPER_H
#define LERPER_H

#include "Vector 2.h"
#include "Shape.h"
#include "Core.h"
#include "SolarSystem.h"
#include "LivingGameEntity.h"
#include "OffsetGraphic.h"

#define MAX_PATH_LENGTH 100

class Lerper : public LivingGameEntity {
	static const float FULL_STARTING_HEALTH;
	static Shape myStyle;
	static Core::RGB myColor;
	static const int distacePerSecond = 100;
	static float turnSpeed;

	float alpha;//current position on line
	float interval;
	Vector2D path[MAX_PATH_LENGTH];
	int numOfWayPoints;//length of path
	int currentLine;
	//using a catched nextLine to prevent errors with adding a newLine dynamically
	Vector2D catchedNextLine;
	
	Vector2D pos;
	float angle;

	SolarSystem bodyGuards;

public:
	void init();
	void addPoint(const Vector2D& toAdd);
	int  nextIndex();
	void nextLine();
	Matrix3D getTransMatrix();
	Shape *getStyle();
	void update(float dt);
	void draw(MyGraphics& graphics);
	int  getTeam();
	Vector2D getPos();
};

#endif