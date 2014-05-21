#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleContact.h>
#include <Timer.h>

class CollisionGUI : public PhysicsGUIBase {
	struct {
		Particle point;
		glm::vec3 startVel;
		VectorGraphic * pointGraphic;
		VectorGraphic * vel;
		VectorGraphic * mom;
	} allPoints[2];
	int numOfNodes;
	glm::vec3 systemMom;
	float totalKineticEnergy;
	ParticleContact collisionManager;
public:
	void init() {
		PhysicsGUIBase::init();
		numOfNodes = 0;
		for (int i = 0; i < 2; i++)
		{
			collisionManager.particle[i] = &allPoints[i].point;

			allPoints[i].point.init(1,(i==0)? .5 : .3);
			allPoints[i].point.pos = (i==0) ? glm::vec3(-3,0,0) : glm::vec3(3,0,0);
			allPoints[i].pointGraphic = addVectorGraphic();
			allPoints[i].startVel = (i==0) ? glm::vec3(1,0,0) : glm::vec3(-1,0,0);
				allPoints[i].pointGraphic->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(0,0,1);
			allPoints[i].vel= addVectorGraphic();
				allPoints[i].vel->displayStyle = DS_ARROW;
				allPoints[i].vel->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(0,0,1);
			allPoints[i].mom= addVectorGraphic();
				allPoints[i].mom->displayStyle = DS_ARROW;
				allPoints[i].mom->color = glm::vec3(0,1,0);
			numOfNodes++;
		}

		reset();
		
		myDebugMenu.button("Reset Particles", fastdelegate::MakeDelegate(this,&CollisionGUI::reset));
		myDebugMenu.slideFloat("Red Mass",  allPoints[0].point.mass, 0.0f, 5.0f);
		myDebugMenu.slideFloat("Blue Mass", allPoints[1].point.mass, 0.0f, 5.0f);
		myDebugMenu.slideFloat("Restitution", collisionManager.restitution, 0, 1);
		myDebugMenu.slideVector("P1 Initial Velocity", allPoints[0].startVel, 0,  10);
		myDebugMenu.slideVector("P2 Initial Velocity", allPoints[1].startVel, 0, -10);
		myDebugMenu.watchVector("P1 Velocity", allPoints[0].point.vel);
		myDebugMenu.watchVector("P2 Velocity", allPoints[1].point.vel);
		myDebugMenu.watchVector("System Momentum",systemMom);
		myDebugMenu.watchFloat("Total Kinetic Energy",totalKineticEnergy);
  

	};
	void reset() {
		allPoints[0].point.pos = glm::vec3(-3,0,0);
		allPoints[0].point.vel = allPoints[0].startVel;
		allPoints[1].point.pos = glm::vec3(3,0,0);
		allPoints[1].point.vel = allPoints[1].startVel;
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		//do stuff here


		systemMom = glm::vec3();
		totalKineticEnergy = 0;
		for (int i = 0; i < numOfNodes; i++)
		{
			allPoints[i].point.update(dt());
			systemMom += allPoints[i].point.momentum;
			totalKineticEnergy += .5 * allPoints[i].point.mass * glm::dot(allPoints[i].point.vel,allPoints[i].point.vel);
		}

		for (int i = 0; i < numOfNodes; i++)
		{
			allPoints[i].point.update(dt());
			allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
			syncVector(allPoints[i].pointGraphic,allPoints[i].point.pos);
			syncVector(allPoints[i].vel,allPoints[i].point.vel,allPoints[i].point.pos);
			syncVector(allPoints[i].mom,allPoints[i].point.momentum,allPoints[i].point.pos);
		}
	}
	bool circleCollide(glm::vec3& object1Pos, float object1Rad, glm::vec3& object2Pos, float object2Rad) {
		glm::vec3 diff = object1Pos - object2Pos;
		float rads = object1Rad + object2Rad;
		return glm::dot(diff,diff) < rads * rads;
	}
};