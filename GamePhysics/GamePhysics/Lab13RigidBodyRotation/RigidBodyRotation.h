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
	void init() {
		PhysicsGUIBase::init(false);

		springs.init(20);

		numOfSpringGraphics = 0;
		
		drag = .96;
		overallAngleVel = .5;

		explode = false;
		throwPower = 5;

		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			myForceReg.add(allRidgidBodies[i].point,springs);
			allRidgidBodies[i].radius = Random::randomFloat(2,3);
			allRidgidBodies[i].angleVel = Random::randomFloat(.5,2);

			allRidgidBodies[i].point.init(1,1);
			allRidgidBodies[i].pointGraphic  = addVectorGraphic();
			allRidgidBodies[i].pointGraphic -> displayStyle = DS_SQUARE;
				
			allRidgidBodies[i].velGraphic  = addVectorGraphic();
			allRidgidBodies[i].velGraphic -> displayStyle = DS_ARROW;
			allRidgidBodies[i].velGraphic -> color = glm::vec3(0,0,0);

			for (int j = 0; j < NUM_OF_PARTICLES; j++)
			{
				allRidgidBodies[i].allPoints[j].point.init(drag,.5);
				allRidgidBodies[i].allPoints[j].pointGraphic  = addVectorGraphic();
				allRidgidBodies[i].allPoints[j].pointGraphic -> color = glm::vec3(0,0,1);
				
				allRidgidBodies[i].allPoints[j].velGraphic  = addVectorGraphic();
				allRidgidBodies[i].allPoints[j].velGraphic -> displayStyle = DS_ARROW;
				allRidgidBodies[i].allPoints[j].velGraphic -> color = glm::vec3(0,1,0);

				allRidgidBodies[i].allPoints[j].radiusVector  = addVectorGraphic();
				allRidgidBodies[i].allPoints[j].radiusVector -> displayStyle = DS_ARROW;
				allRidgidBodies[i].allPoints[j].radiusVector -> color = glm::vec3(.7,.7,.7);
				
				allRidgidBodies[i].allPoints[j].angleVelGraphic  = addVectorGraphic();
				allRidgidBodies[i].allPoints[j].angleVelGraphic -> displayStyle = DS_ARROW;
				allRidgidBodies[i].allPoints[j].angleVelGraphic -> color = glm::vec3(.7,.7,0);
			}
		}

		resetRandom();

		myDebugMenu.button("Throw",fastdelegate::MakeDelegate(this,&RigidBodyRotation::launch));
		myDebugMenu.button("Reset\nPerfect",fastdelegate::MakeDelegate(this,&RigidBodyRotation::resetCircle));
		myDebugMenu.button("Reset\nRandom",fastdelegate::MakeDelegate(this,&RigidBodyRotation::resetRandom));
		myDebugMenu.button("Remove\nSprings",fastdelegate::MakeDelegate(this,&RigidBodyRotation::wipeSprings));
		myDebugMenu.edit("Throw Power",throwPower,0,10);
		myDebugMenu.edit("Explode",explode);
		myDebugMenu.edit("Drag",drag, 0, 1);
		myDebugMenu.edit("Angle Vel",overallAngleVel, 0, 5);
	};
	void launch() {
		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			glm::vec3 dir = Random::glmRand::randomUnitVector();
			dir.z = 0;
			dir = glm::normalize(dir);
			allRidgidBodies[i].point.vel = dir * throwPower;
		}
	}
	void reset(float lowRange) {
		float bodyRadius = 5;
		float bodyAngleOffset = 360 / NUM_OF_BODIES;
		float bodyCurrentAngle = 0;

		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			allRidgidBodies[i].point.pos = bodyRadius * glm::rotate(glm::vec3(0,1,0),bodyCurrentAngle,glm::vec3(0,0,1));
			allRidgidBodies[i].point.vel = glm::vec3();
			bodyCurrentAngle += bodyAngleOffset;

			allRidgidBodies[i].angleVel = 1;

			float angleOffset = 360 / NUM_OF_PARTICLES;
			float currentAngle = 0;
			glm::vec3 startingPos = glm::vec3(0,1,0);
			for (int j = 0; j < NUM_OF_PARTICLES; j++)
			{
				allRidgidBodies[i].allPoints[j].radiusPercent = Random::randomFloat(lowRange,1);
				glm::vec3 posOffset = glm::rotate(startingPos,currentAngle,glm::vec3(0,0,1));
				posOffset *= allRidgidBodies[i].radius * allRidgidBodies[i].allPoints[j].radiusPercent;
				currentAngle += angleOffset;


				allRidgidBodies[i].allPoints[j].point.init(1,.5);
				allRidgidBodies[i].allPoints[j].point.vel = glm::vec3();
				allRidgidBodies[i].allPoints[j].point.pos = allRidgidBodies[i].point.pos + posOffset;
			}
		}
		//setting up forces
		springs.clear();
		int springGraphicIndex = 0;
		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			for (int j = 0; j < NUM_OF_BODIES; j++)
			{
				if(i!=j) {
					float length = glm::length(allRidgidBodies[i].point.pos - allRidgidBodies[j].point.pos);
					springs.addSpring(allRidgidBodies[i].point,allRidgidBodies[j].point.pos,length);
					if(springGraphicIndex >= numOfSpringGraphics) { // need to expand array
						springGraphics[numOfSpringGraphics].graphic  = addVectorGraphic();
						springGraphics[numOfSpringGraphics].graphic -> displayStyle = DS_ARROW;
						springGraphics[numOfSpringGraphics].graphic -> color = glm::vec3(0,1,1);
						numOfSpringGraphics++;
					}
					springGraphics[springGraphicIndex].graphic->visible = true;
					springGraphics[springGraphicIndex].from = &allRidgidBodies[i].point;
					springGraphics[springGraphicIndex].anchor = &allRidgidBodies[j].point.pos;
					springGraphicIndex++;
				}
			}
		}
		//hiding all the excess
		for (int i = springGraphicIndex; i < numOfSpringGraphics; i++)
		{
			springGraphics[i].graphic->visible = false;
		}
	}
	void resetRandom() {
		reset(.2);
	}
	void resetCircle() {
		reset(1);
	}

	void wipeSprings() {
		springs.clear();
		for (int i = 0; i < numOfSpringGraphics; i++)
		{
			springGraphics[i].graphic->visible = false;
		}
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		myForceReg.updateForces();

		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			allRidgidBodies[i].point.drag = drag;
			allRidgidBodies[i].angleVel = overallAngleVel;
			allRidgidBodies[i].point.update(dt());
			for (int j = 0; j < NUM_OF_PARTICLES; j++)
			{
				allRidgidBodies[i].allPoints[j].point.update(dt());
				if(!explode) {
					allRidgidBodies[i].allPoints[j].cashedRadius = allRidgidBodies[i].radius * allRidgidBodies[i].allPoints[j].radiusPercent;
					glm::vec3 rad = allRidgidBodies[i].allPoints[j].cashedRadius * glm::normalize(allRidgidBodies[i].allPoints[j].point.pos - allRidgidBodies[i].point.pos);
					allRidgidBodies[i].allPoints[j].point.pos = allRidgidBodies[i].point.pos + rad;
					glm::vec3 perp = glm::perp(rad,glm::vec3(0,0,1));
					perp = glm::vec3(-rad.y,rad.x,0);
					allRidgidBodies[i].allPoints[j].angleVel = perp * allRidgidBodies[i].angleVel;
					allRidgidBodies[i].allPoints[j].point.vel = allRidgidBodies[i].allPoints[j].angleVel + allRidgidBodies[i].point.vel;
				}
			}
		}

		redraw();
	}
	void redraw() {
		for (int i = 0; i < NUM_OF_BODIES; i++)
		{
			allRidgidBodies[i].pointGraphic->pointSize = allRidgidBodies[i].point.mass;
			sync(allRidgidBodies[i].pointGraphic,allRidgidBodies[i].point.pos);
			sync(allRidgidBodies[i].velGraphic,allRidgidBodies[i].point.vel,allRidgidBodies[i].point.pos);

			for (int j = 0; j < NUM_OF_PARTICLES; j++)
			{
				allRidgidBodies[i].allPoints[j].pointGraphic->pointSize = allRidgidBodies[i].allPoints[j].point.mass;

				glm::vec3 vec = allRidgidBodies[i].allPoints[j].point.pos;
				glm::vec3 pos = allRidgidBodies[i].allPoints[j].point.pos;
				sync(allRidgidBodies[i].allPoints[j].pointGraphic, pos);
				
				vec = allRidgidBodies[i].allPoints[j].point.vel;
				pos = allRidgidBodies[i].allPoints[j].point.pos;
				sync(allRidgidBodies[i].allPoints[j].velGraphic, vec, pos);
				
				vec = allRidgidBodies[i].allPoints[j].cashedRadius * glm::normalize(allRidgidBodies[i].allPoints[j].point.pos - allRidgidBodies[i].point.pos);
				pos = allRidgidBodies[i].point.pos;
				sync(allRidgidBodies[i].allPoints[j].radiusVector, vec, pos);


				vec = allRidgidBodies[i].allPoints[j].angleVel;
				pos = allRidgidBodies[i].allPoints[j].point.pos;
				sync(allRidgidBodies[i].allPoints[j].angleVelGraphic, vec, pos);
			}
		}
		for (int i = 0; i < numOfSpringGraphics; i++)
		{
			glm::vec3 diff = *springGraphics[i].anchor - springGraphics[i].from->pos;
			sync(springGraphics[i].graphic, diff, springGraphics[i].from->pos);
		}
	}



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