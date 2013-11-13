#pragma once
#include "Vector 2.h"
#include <cassert>
#include "Shape.h"
#include "Core.h"
#include "SolarSystem.h"

#define MAX_PATH_LENGTH 100

class Lerper {
	static Shape myStyle;
	static Core::RGB myColor;
	static const int distacePerSecond = 100;
	int currentLine;
	float alpha;//current position on line
	float interval;
	Vector2D pos;//position in space
	Vector2D path[MAX_PATH_LENGTH];
	Vector2D catchedNextLine;
	int pathLength;
	static float turnSpeed;
	float angle;

	SolarSystem bodyGuards;

public:
	void init();
	void addPoint(const Vector2D& toAdd);
	int  nextIndex();
	void nextLine();
	void update(float dt);
	void draw(Core::Graphics& graphics);
};