#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleContact.h>
#include <Timer.h>
#include <CollisionMassCircles.h>

class CollisionGUI : public PhysicsGUIBase {
	Timer mouseDragTimer;
	struct {
		Particle point;
		glm::vec3 startVel;
		VectorGraphic * pointGraphic;
		VectorGraphic * vel;
		VectorGraphic * mom;
		VectorGraphic * collideVel;
	} allPoints[2];
	int numOfNodes;
	glm::vec3 systemMom;
	float totalKineticEnergy;
	ParticleContact collisionData;
	CollisionMassCircles collisionManager;
public:
	void init() {
		PhysicsGUIBase::init();
		mouseDragTimer.start();
		numOfNodes = 0;
		collisionData.restitution = 1;
		for (int i = 0; i < 2; i++)
		{
			collisionData.particle[i] = &allPoints[i].point;

			allPoints[i].point.init(1,(i==0)? .5 : .3);
			allPoints[i].point.pos = (i==0) ? glm::vec3(-3,0,0) : glm::vec3(3,0,0);
			allPoints[i].pointGraphic = addVectorGraphic();
			allPoints[i].startVel = (i==0) ? glm::vec3(1,0,0) : glm::vec3(-1,0,0);
				allPoints[i].pointGraphic->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(0,0,1);
			allPoints[i].vel= addVectorGraphic();
				allPoints[i].vel->displayStyle = DS_ARROW;
				allPoints[i].vel->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(1,0,0);
			allPoints[i].mom= addVectorGraphic();
				allPoints[i].mom->displayStyle = DS_ARROW;
				allPoints[i].mom->color = glm::vec3(0,0,1);
			allPoints[i].collideVel= addVectorGraphic();
				allPoints[i].collideVel->displayStyle = DS_ARROW;
				allPoints[i].collideVel->color = glm::vec3(0,1,0);
			numOfNodes++;
		}

		collisionManager.init(&allPoints[0].point,&allPoints[1].point);

		reset();
		
		myDebugMenu.button("Reset Particles", fastdelegate::MakeDelegate(this,&CollisionGUI::reset));
		myDebugMenu.button("Cause Collision", fastdelegate::MakeDelegate(this,&CollisionGUI::collide));
		myDebugMenu.slideFloat("Red Mass",  allPoints[0].point.mass, 0.0f, 5.0f);
		myDebugMenu.slideFloat("Blue Mass", allPoints[1].point.mass, 0.0f, 5.0f);
		myDebugMenu.slideFloat("Restitution", collisionData.restitution, 0, 1);
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
		
		if(mouseDragTimer.stop() > dt()*10) {
			collisionManager.update();
			if(collisionManager.hasCollided()) {
				collisionData.contactNormal = collisionManager.getNormal();
				collisionData.penetration = collisionManager.getPenetration();
				collisionData.collide(dt());
			}


			systemMom = glm::vec3();
			totalKineticEnergy = 0;
			for (int i = 0; i < numOfNodes; i++)
			{
				allPoints[i].point.update(dt());
				systemMom += allPoints[i].point.momentum;
				totalKineticEnergy += .5 * allPoints[i].point.mass * glm::dot(allPoints[i].point.vel,allPoints[i].point.vel);
			}
		}

		redraw();
	}
	void collide() {
		collisionData.contactNormal = collisionManager.getNormal();
		collisionData.penetration = collisionManager.getPenetration();
		collisionData.collide(dt());
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		mouseDragTimer.start();
		int index = vectorGraphicIndex / 4; // 2 graphics made for each point
		allPoints[index].point.pos += dragDelta;

		collisionManager.update();

		redraw();
	}
	void redraw() {
		for (int i = 0; i < numOfNodes; i++)
		{
			allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
			syncVector(allPoints[i].pointGraphic,allPoints[i].point.pos);
			syncVector(allPoints[i].vel,allPoints[i].point.vel,allPoints[i].point.pos);
			syncVector(allPoints[i].mom,allPoints[i].point.momentum,allPoints[i].point.pos);
			syncVector(allPoints[i].collideVel,collisionManager.vels[i],allPoints[i].point.pos);
		}
	}
};