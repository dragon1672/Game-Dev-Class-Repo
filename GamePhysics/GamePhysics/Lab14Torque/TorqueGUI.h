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
	
	static const int NUM_OF_PARTICLES = 14;
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
		
		float totalInertia;
	} ridgidBody;
	
	bool explode;
	float throwPower;

	float drag;
	
	struct {
		glm::vec3 lever;
		glm::vec3 force;
		glm::vec3 perpForce;
		VectorGraphic * leverGraphic;
		VectorGraphic * forceGraphic;
		VectorGraphic * perpGraphic;
	} lever;

	void initGraphic(VectorGraphic** leGraphic, glm::vec3& col) {
		(*leGraphic)  = addVectorGraphic();
		(*leGraphic) -> displayStyle = DS_ARROW;
		(*leGraphic) -> color = col;
	}
public:
	void init() {
		PhysicsGUIBase::init(false);

		drag = .96;

		explode = false;
		throwPower = 5;

		ridgidBody.radius = Random::randomFloat(2,3);
		ridgidBody.angleVel = Random::randomFloat(.5,2);
		
		ridgidBody.point.init(1,.3);
		ridgidBody.pointGraphic  = addVectorGraphic();
		ridgidBody.pointGraphic -> displayStyle = DS_SQUARE;
		
		ridgidBody.velGraphic  = addVectorGraphic();
		ridgidBody.velGraphic -> displayStyle = DS_ARROW;
		ridgidBody.velGraphic -> color = glm::vec3(0,0,0);

		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].pointGraphic  = addVectorGraphic();
			ridgidBody.allPoints[j].pointGraphic -> color = glm::vec3( 0, 0, 1);

			initGraphic(&ridgidBody.allPoints[j].velGraphic,      glm::vec3( 0, 1, 0));
			initGraphic(&ridgidBody.allPoints[j].radiusVector,    glm::vec3(.7,.7,.7));
			initGraphic(&ridgidBody.allPoints[j].angleVelGraphic, glm::vec3(.7,.7, 0));
		}
		initGraphic(&lever.forceGraphic, glm::vec3(0,.3,.8));
		initGraphic(&lever.leverGraphic, glm::vec3(0, 0, 0));
		initGraphic(&lever.perpGraphic,  glm::vec3(0,.8,.3));

		resetRandom();

		myDebugMenu.button("Throw",fastdelegate::MakeDelegate(this,&TorqueGUI::launch));
		myDebugMenu.button("Reset\nPerfect",fastdelegate::MakeDelegate(this,&TorqueGUI::resetCircle));
		myDebugMenu.button("Reset\nRandom",fastdelegate::MakeDelegate(this,&TorqueGUI::resetRandom));
		myDebugMenu.edit("Throw Power",throwPower,0,10);
		myDebugMenu.edit("Explode",explode);
		myDebugMenu.edit("Drag",drag, 0, 1);
		myDebugMenu.watch("Angle Vel",ridgidBody.angleVel);
		myDebugMenu.watch("Total Inertia",ridgidBody.totalInertia);
		myDebugMenu.edit("Radius", ridgidBody.radius, .01, 20);
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
		ridgidBody.totalInertia = 0;
		lever.lever = glm::vec3();
		lever.force = glm::vec3();
		lever.perpForce = glm::vec3();

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

			ridgidBody.allPoints[j].point.init(1,Random::randomFloat(.2,1));
			ridgidBody.allPoints[j].point.vel = glm::vec3();
			ridgidBody.allPoints[j].point.pos = ridgidBody.point.pos + posOffset;

			ridgidBody.totalInertia += glm::dot(ridgidBody.allPoints[j].point.pos,ridgidBody.allPoints[j].point.pos) * ridgidBody.allPoints[j].point.mass;
		}
	}
	void resetRandom() {
		reset(.2);
	}
	void resetCircle() {
		reset(1);
	}

	void leverUpdate() {
		if(GetAsyncKeyState(VK_LBUTTON)) {
			lever.lever = getMousePosition() - ridgidBody.point.pos;
		} else if(GetAsyncKeyState(VK_RBUTTON) && lever.lever != glm::vec3()) {
			lever.force =  getMousePosition() - lever.lever - ridgidBody.point.pos;
			lever.perpForce = glm::perp(lever.force, glm::normalize(lever.lever));
		}
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		if(!explode && ridgidBody.totalInertia != 0) {
			leverUpdate();
		
			glm::vec3 totalTorque = glm::cross(lever.lever, lever.perpForce);
			glm::vec3 angularAcceleration = (totalTorque/ridgidBody.totalInertia)*dt();
			ridgidBody.angleVel += angularAcceleration.z;
		}

		ridgidBody.point.drag = drag;
		ridgidBody.point.update(dt());

		ridgidBody.totalInertia = 0;
		for (int j = 0; j < NUM_OF_PARTICLES; j++)
		{
			ridgidBody.allPoints[j].point.update(dt());
			if(!explode) {
				ridgidBody.allPoints[j].cashedRadius = ridgidBody.radius * ridgidBody.allPoints[j].radiusPercent;
				glm::vec3 rad = ridgidBody.allPoints[j].cashedRadius * glm::normalize(ridgidBody.allPoints[j].point.pos - ridgidBody.point.pos);
				ridgidBody.allPoints[j].point.pos = ridgidBody.point.pos + rad;
				glm::vec3 perp = glm::perp(rad,glm::vec3(0,0,1));
				perp = glm::vec3(-rad.y,rad.x,rad.z);
				ridgidBody.allPoints[j].angleVel = perp * ridgidBody.angleVel;
				ridgidBody.allPoints[j].point.vel = ridgidBody.allPoints[j].angleVel + ridgidBody.point.vel;

				ridgidBody.totalInertia += glm::dot(ridgidBody.allPoints[j].point.pos,ridgidBody.allPoints[j].point.pos) * ridgidBody.allPoints[j].point.mass;
			}
		}
		redraw();
	}
	void redraw() {
		ridgidBody.pointGraphic->pointSize = ridgidBody.point.mass;
		sync(ridgidBody.pointGraphic,ridgidBody.point.pos);
		sync(ridgidBody.velGraphic,ridgidBody.point.vel,ridgidBody.point.pos);
		
		
		sync(lever.forceGraphic, lever.force,     ridgidBody.point.pos + lever.lever);
		sync(lever.leverGraphic, lever.lever,     ridgidBody.point.pos              );
		sync(lever.perpGraphic,  lever.perpForce, ridgidBody.point.pos + lever.lever);

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