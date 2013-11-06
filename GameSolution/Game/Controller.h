#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Boundary.h"
#include "HUD.h"
#include "Vector 2.h"
#include "GameSpace.h"

class Controller {
	int width;
	int height;
	HUD hud;
	GameSpace myWorld;
	Vector2D boundPoints[10];
	Boundary bounds;
	int numOfBoundPoints;
public:
	Controller (int width, int height) :
	width(width), 
	height(height), 
	hud(width,height),
	myWorld(hud.getWorldWidth(),hud.getWorldHeight(),hud.getWorldoffset()) {
		numOfBoundPoints = 0;
		Vector2D worldPos = hud.getWorldoffset();
		float worldWidth    = hud.getWorldWidth();
		float worldHeight   = hud.getWorldHeight();
		boundPoints[numOfBoundPoints++] = worldPos;
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(0,            (worldPos.getY()+worldHeight)/2);
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(25,           (worldPos.getY()+worldHeight)-100);
		boundPoints[numOfBoundPoints++] = Vector2D(.5f*worldWidth, (worldPos.getY()+worldHeight));
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(worldWidth,   worldHeight/2);
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(worldWidth/2, 0);
		bounds.init(numOfBoundPoints,boundPoints);
		myWorld.registerBoundary(&bounds);
	}
	bool update(float dt) {
		return myWorld.update(dt);
	}
	void draw(Core::Graphics graphics) {
		hud.draw(graphics);
		myWorld.draw(graphics);
	}
};


#endif