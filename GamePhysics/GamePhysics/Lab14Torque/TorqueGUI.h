#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <glm/gtx/perpendicular.hpp>
#include <MyRandom.h>
#include <glm/gtx/rotate_vector.hpp>

class TorqueGUI : public PhysicsGUIBase {
	
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
	} ridgidBody;
	
	bool explode;
	float throwPower;

	float drag;

public:
	void init() {
		PhysicsGUIBase::init(false);

		drag = .96;

		explode = false;
		throwPower = 5;

		ridgidBody.radius = Random::randomFloat(2,3);
		ridgidBody.angleVel = Random::randomFloat(.5,2);
		
		ridgidBody.point.init(1,1);
		ridgidBody.pointGraphic  = addVectorGraphic();
		ridgidBody.pointGraphic -> displayStyle = DS_SQUARE;
		
		ridgidBody.velGraphic  = addVectorGraphic();
		ridgidBody.velGraphic -> displayStyle = DS_ARROW;
		ridgidBody.velGraphic -> color = glm::vec3(0,0,0);

		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].point.init(drag,.5);
			ridgidBody.allPoints[j].pointGraphic  = addVectorGraphic();
			ridgidBody.allPoints[j].pointGraphic -> color = glm::vec3(0,0,1);
				
			ridgidBody.allPoints[j].velGraphic  = addVectorGraphic();
			ridgidBody.allPoints[j].velGraphic -> displayStyle = DS_ARROW;
			ridgidBody.allPoints[j].velGraphic -> color = glm::vec3(0,1,0);

			ridgidBody.allPoints[j].radiusVector  = addVectorGraphic();
			ridgidBody.allPoints[j].radiusVector -> displayStyle = DS_ARROW;
			ridgidBody.allPoints[j].radiusVector -> color = glm::vec3(.7,.7,.7);
				
			ridgidBody.allPoints[j].angleVelGraphic  = addVectorGraphic();
			ridgidBody.allPoints[j].angleVelGraphic -> displayStyle = DS_ARROW;
			ridgidBody.allPoints[j].angleVelGraphic -> color = glm::vec3(.7,.7,0);
		}

		resetRandom();

		myDebugMenu.button("Throw",fastdelegate::MakeDelegate(this,&TorqueGUI::launch));
		myDebugMenu.button("Reset\nPerfect",fastdelegate::MakeDelegate(this,&TorqueGUI::resetCircle));
		myDebugMenu.button("Reset\nRandom",fastdelegate::MakeDelegate(this,&TorqueGUI::resetRandom));
		myDebugMenu.edit("Throw Power",throwPower,0,10);
		myDebugMenu.edit("Explode",explode);
		myDebugMenu.edit("Drag",drag, 0, 1);
		myDebugMenu.watch("Angle Vel",ridgidBody.angleVel);
	}
	void launch() {
		glm::vec3 dir = Random::glmRand::randomUnitVector();
		dir.z = 0;
		dir = glm::normalize(dir);
		ridgidBody.point.vel = dir * throwPower;
	}
	void reset(float lowRange) {
		ridgidBody.point.pos = glm::vec3();
		ridgidBody.point.vel = glm::vec3();

		ridgidBody.angleVel = 0;

		float angleOffset = 360 / NUM_OF_PARTICLES;
		float currentAngle = 0;
		glm::vec3 startingPos = glm::vec3(0,1,0);
		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].radiusPercent = Random::randomFloat(lowRange,1);
			glm::vec3 posOffset = glm::rotate(startingPos,currentAngle,glm::vec3(0,0,1));
			posOffset *= ridgidBody.radius * ridgidBody.allPoints[j].radiusPercent;
			currentAngle += angleOffset;


			ridgidBody.allPoints[j].point.init(1,.5);
			ridgidBody.allPoints[j].point.vel = glm::vec3();
			ridgidBody.allPoints[j].point.pos = ridgidBody.point.pos + posOffset;
		}
	}
	void resetRandom() {
		reset(.2);
	}
	void resetCircle() {
		reset(1);
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();

		ridgidBody.point.drag = drag;
		ridgidBody.point.update(dt());
		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].point.update(dt());
			if(!explode) {
				ridgidBody.allPoints[j].cashedRadius = ridgidBody.radius * ridgidBody.allPoints[j].radiusPercent;
				glm::vec3 rad = ridgidBody.allPoints[j].cashedRadius * glm::normalize(ridgidBody.allPoints[j].point.pos - ridgidBody.point.pos);
				ridgidBody.allPoints[j].point.pos = ridgidBody.point.pos + rad;
				glm::vec3 perp = glm::perp(rad,glm::vec3(0,0,1));
				perp = glm::vec3(-rad.y,rad.x,0);
				ridgidBody.allPoints[j].angleVel = perp * ridgidBody.angleVel;
				ridgidBody.allPoints[j].point.vel = ridgidBody.allPoints[j].angleVel + ridgidBody.point.vel;
			}
		}
		redraw();
	}
	void redraw() {
		ridgidBody.pointGraphic->pointSize = ridgidBody.point.mass;
		sync(ridgidBody.pointGraphic,ridgidBody.point.pos);
		sync(ridgidBody.velGraphic,ridgidBody.point.vel,ridgidBody.point.pos);

		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].pointGraphic->pointSize = ridgidBody.allPoints[j].point.mass;

			glm::vec3 vec = ridgidBody.allPoints[j].point.pos;
			glm::vec3 pos = ridgidBody.allPoints[j].point.pos;
			sync(ridgidBody.allPoints[j].pointGraphic, pos);
				
			vec = ridgidBody.allPoints[j].point.vel;
			pos = ridgidBody.allPoints[j].point.pos;
			sync(ridgidBody.allPoints[j].velGraphic, vec, pos);
				
			vec = ridgidBody.allPoints[j].cashedRadius * glm::normalize(ridgidBody.allPoints[j].point.pos - ridgidBody.point.pos);
			pos = ridgidBody.point.pos;
			sync(ridgidBody.allPoints[j].radiusVector, vec, pos);
			ridgidBody.allPoints[j].radiusVector -> visible = !explode;


			vec = ridgidBody.allPoints[j].angleVel;
			pos = ridgidBody.allPoints[j].point.pos;
			sync(ridgidBody.allPoints[j].angleVelGraphic, vec, pos);
			ridgidBody.allPoints[j].angleVelGraphic -> visible = !explode;
		}
	}
};