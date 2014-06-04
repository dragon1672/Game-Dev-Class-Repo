//*
#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <glm/gtx/perpendicular.hpp>
#include <MyRandom.h>
#include <glm/gtx/rotate_vector.hpp>
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <ParticleForceRegistry.h>

class RigidBodyRotation : public PhysicsGUIBase {
	
	ParticleForceRegistry myForceReg;
	SpringForceGenerator springs;

	static const int NUM_OF_BODIES = 6;
	static const int NUM_OF_PARTICLES = 10;
	struct {
		struct {
			Particle point;
			float radiusPercent;
			glm::vec3 angleVel;
			float cashedRadius;
			VectorGraphic * pointGraphic;
			VectorGraphic * velGraphic;
			VectorGraphic * angleVelGraphic;
			VectorGraphic * radiusVector;
		} allPoints[NUM_OF_PARTICLES];
		Particle point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
		float radius;
		float angleVel;
	} allRidgidBodies[NUM_OF_BODIES];
	
	bool explode;
	float throwPower;

	float overallAngleVel;
	float drag;



	struct {
		Particle * from;
		glm::vec3 * anchor;
		VectorGraphic * graphic;
	} springGraphics[NUM_OF_BODIES * NUM_OF_BODIES];
	uint numOfSpringGraphics;


public:
	void init();
	void launch();
	void reset(float lowRange);
	void resetRandom();
	void resetCircle();

	void wipeSprings();

	void newFrame();
	void redraw();



	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		int numOfGraphicsPerEntity =  NUM_OF_PARTICLES * 4 + 2; // yay magic :D
		bool clickingEntireEntity = vectorGraphicIndex % numOfGraphicsPerEntity == 0;
		if(clickingEntireEntity) {
			int index = vectorGraphicIndex / numOfGraphicsPerEntity;
			allRidgidBodies[index].point.pos += dragDelta;
		}

		redraw();
	}
};
//*/