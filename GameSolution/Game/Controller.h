#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Boundary.h"
#include "HUD.h"
#include "Vector 2.h"
#include "GameSpace.h"

//#define DEBUG_CONTROLLER

#ifdef DEBUG_CONTROLLER
#include <sstream>
#endif//DEBUG_CONTROLLER




#include <random>
int randomnumber(int low, int high) {
	std::random_device rd;//dont like making multiple engines
	std::mt19937 mt(rd()); //seed
	std::uniform_int_distribution<int>dist(low,high);
	return dist(mt);
}
Vector2D *generateRandomPolygon(int sides) {
	float variancePercent = 15;
	float wallLengthDiff = 20;
	float averageAngle = ((sides-2)*360)/sides;
	float variance = averageAngle / variancePercent;
	Vector2D points[100];
	points[0] = Vector2D(0,0);
	points[1] = Vector2D(0,5);
	points[2] = Vector2D(4,7);
	points[3] = Vector2D(10,5);
	points[4] = Vector2D(7,5);

	/*
	Vector2D lastWall = points[1] - points[0];
	for(int i=1;i<sides-1;i++) {
		float angle = averageAngle+randomnumber(-variance,variance);
		Vector2D newWall = Matrix3D::rotationMatrix(angle) * lastWall.normalized();
		newWall = newWall * randomnumber(100,100+wallLengthDiff);
		points[i+1] = points[i] + newWall;
	}//*/
	return points;
}






class Controller {
	int width;
	int height;
	HUD hud;
	GameSpace myWorld;
	Vector2D boundPoints[10];
	Boundary bounds;
	int numOfBoundPoints;
#ifdef DEBUG_CONTROLLER
	int FPS;
#endif//DEBUG_CONTROLLER
public:
	Controller (int width, int height) :
	width(width), 
	height(height), 
	hud(width,height),
	myWorld(hud.getWorldWidth(),hud.getWorldHeight(),hud.getWorldoffset()) {
#ifdef DEBUG_CONTROLLER
		FPS = 0;
#endif//DEBUG_CONTROLLER
		numOfBoundPoints = 0;
		Vector2D worldPos = hud.getWorldoffset();
		float padding = 5;
		float worldWidth    = hud.getWorldWidth();
		float worldHeight   = hud.getWorldHeight();
		//*generate shape with random line and then generate random angle and have awesomeness ensue
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(padding,padding);//top right
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(padding,      (worldPos.getY()+worldHeight)/2-padding);//left
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(.1f*worldWidth,(worldHeight)-padding);
		boundPoints[numOfBoundPoints++] = Vector2D(.5f*worldWidth,        (worldPos.getY()+worldHeight)-padding);
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(worldWidth-padding,   worldHeight/2);
		boundPoints[numOfBoundPoints++] = worldPos+Vector2D(.7f*worldWidth, padding);
		bounds.init(numOfBoundPoints,boundPoints);
		//*/
		/*random bounds
		int sides = 5;
		Vector2D *randomPoly = generateRandomPolygon(sides);
		Matrix3D scaler = Matrix3D::scaleX(worldWidth-padding) * Matrix3D::scaleY(worldHeight-padding);
		bounds.init(sides,randomPoly,scaler);
		//*/
		
		myWorld.registerBoundary(&bounds);
	}
	bool update(float dt) {
#ifdef DEBUG_CONTROLLER
		FPS = (int)(1/dt);
#endif//DEBUG_CONTROLLER
		return myWorld.update(dt);
	}
	void draw(Core::Graphics graphics) {
		hud.draw(graphics);
		myWorld.draw(graphics);
#ifdef DEBUG_CONTROLLER
		std::stringstream ss;
		ss << FPS;
		std::string fps = ss.str();
		graphics.DrawString(0,0,fps.c_str());
#endif//DEBUG_CONTROLLER
	}
};


#endif