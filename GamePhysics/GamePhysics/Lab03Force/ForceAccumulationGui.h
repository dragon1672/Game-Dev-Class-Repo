#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <VectorBoundForceGenerator.h>
#include <GravityForceGenerator.h>

class ForceAccumulationGui : public PhysicsGUIBase {
protected:
	struct {
		Particle * point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
		VectorGraphic * magGraphic;
	} allPoints[3];
	int numOfPoints;
	Particle one;
	Particle two;
	Particle thr;
	glm::vec3 keyboardInput;
	ParticleForceRegistry forceManager;
	VectorBoundForceGenerator keyboardForce;
	GravityForceGenerator gravForce;
public:
	void init();
	void newFrame();
};