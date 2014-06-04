#pragma once

#include "../PhysicsGUIBase.h"
#include <CollisionManager.h>
#include <Timer.h>
#include <GravityForceGenerator.h>
#include <ParticleForceRegistry.h>
#include <Ray.h>
#include <MyRandom.h>

class RestingContactGUI : public PhysicsGUIBase {
	Timer mouseDragTimer;

	static const int MAX_TOTAL_POINTS = 201;
	static const int STARTING_NUM_OF_POINTS = 4;

	float resetNumOfParticles;
	glm::vec3 sideMovingStart;

	struct {
		Particle point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
	} allPoints[MAX_TOTAL_POINTS];
	int numOfPoints;

	Ray wall;
	VectorGraphic * wallGraphicLeft;
	VectorGraphic * wallGraphicRight;

	CollisionManager collisionManager;
	ParticleForceRegistry forceReg;
	GravityForceGenerator gravity;
public:
	void init();
	void reset();
	void newFrame();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
	void redraw();
};


/* lab requirements
	1-	Particles falls down on top of each other to the ground.
	2-	Apply gravity.
	3-	Particles stand on top of each other making a pillar.
	4-	Particle come in from left and knocks the tower down.
	5-	Tower falls down in a realistic manner.
	6-	Reasonable UI controls (don’t make me stand on my head).
//*/