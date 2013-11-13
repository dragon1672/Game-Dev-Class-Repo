#pragma once
#ifndef GAMESPACE_H
#define GAMESPACE_H

#include "Shape.h"
#include "Boundary.h"
#include "SpaceShip.h"
#include "Lerper.h"

const Core::RGB defaultColor = RGB(255,0,50);
//creates a sqare world where all game obects will interact in
class GameSpace {
	Spaceship myShip;
	Boundary *boundary;
	Lerper myLerp;
	Vector2D min;
	Vector2D max;
	Shape toDraw;
	void initObjects();
	void makeGameSpace(Core::RGB color, float width, float height, Vector2D pos);
	bool hasBounds;
public:
	bool temp;
	GameSpace();
	GameSpace(float width, float height, const Vector2D& pos=Vector2D(0,0), Core::RGB color=defaultColor);
	void      registerBoundary(Boundary *bounds);
	void      draw(Core::Graphics& graphics);
	bool      update(float dt);
	Boundary *getBoundary();
	Vector2D  getMin();
	Vector2D  getMax();
	Vector2D  collideVector(const Vector2D& pos, const Vector2D& vel);
	Vector2D  randomWorldPoint();
	Vector2D  getCenter();
};

#endif