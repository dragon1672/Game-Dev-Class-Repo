#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <VectorBoundForceGenerator.h>
#include <DragForceGenerator.h>
#include <Timer.h>

class SpringGUI : public PhysicsGUIBase {
	GravityForceGenerator myGrav;
	SpringForceGenerator mySprings;
	DragForceGenerator myDrag;

	ParticleForceRegistry forceManager;

	Timer mouseDragTimer;

	bool toggleChain;
	bool toggleChain_last;
	bool toggleDoubleChain;
	bool toggleDoubleChain_last;
	bool toggleFull;
	bool toggleFull_last;
	bool toggleSep;
	bool toggleSep_last;

	float dragConst;

	Particle particalMem[10];
	int numOfParticles;
	struct {
		Particle * point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
		VectorGraphic * magGraphic;
	} allPoints[10];
	int numOfPoints;
	struct springRayStruct {
		glm::vec3 * from;
		glm::vec3 * to;
		VectorGraphic * graphic;
	} springRays[20];
	int numOfSpringRays;
public:
	void init();
	void newFrame();
	void toggleChangFun();
	void toggleChangDoubleFun();
	void toggleComplexFun();
	void updateForces();
	void wipeSprings();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
};