#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <Timer.h>

class WaveGui : public PhysicsGUIBase {
	SpringForceGenerator mySprings;
	DragForceGenerator myDrag;
	GravityForceGenerator myGrav;
	ParticleForceRegistry forceManager;

	float dragConst;
	float startingY;
	float endingY;
	float speed;
	float range;

	static const int NUM_OF_NODES = 50;

	struct {
		Particle point;
		VectorGraphic * pointGraphic;
	} allPoints[NUM_OF_NODES];
	int numOfNodes;

	struct springRayStruct {
		glm::vec3 * from;
		glm::vec3 * to;
		VectorGraphic * graphic;
	} springRays[NUM_OF_NODES];
public:
	void init();
	void newFrame();
};