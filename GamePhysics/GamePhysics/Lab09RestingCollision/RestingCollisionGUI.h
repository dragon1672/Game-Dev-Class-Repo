#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleContact.h>
#include <Timer.h>
#include <CollisionMassWall.h>
#include <GravityForceGenerator.h>
#include <Ray.h>

class RestingCollisionGUI : public PhysicsGUIBase {
	Timer mouseDragTimer;
	Particle point;
	VectorGraphic * pointGraphic;
	VectorGraphic * vel;
	VectorGraphic * mom;
	VectorGraphic * wallGraphicLeft;
	VectorGraphic * wallGraphicRight;
	Ray wall;
	VectorGraphic * wallGraphic;

	glm::vec3 preCollisionForce;
	glm::vec3 preCollisionVel;
	glm::vec3 postCollisionForce;
	glm::vec3 postCollisionVel;
	glm::vec3 gravity;


	ParticleContact collisionData;
	CollisionMassWall collisionManager;
public:
	void init() {
		PhysicsGUIBase::init();
		mouseDragTimer.start();
		gravity = glm::vec3(0,-9.81,0);
		wall.origin = glm::vec3();
		wall.direction =  glm::vec3(0,1,0);
		collisionData.restitution = .8f;

		collisionData.particle[0] = &point;
		collisionData.particle[1] = nullptr;
		point.init(.95f,1);
		pointGraphic = addVectorGraphic();
		pointGraphic->color = glm::vec3(1,0,0);
		mom = addVectorGraphic();
		mom->displayStyle = DS_ARROW;
		mom->color = glm::vec3(0,0,1);
		vel= addVectorGraphic();
		vel->displayStyle = DS_ARROW;
		vel->color = glm::vec3(0,1,0);

		wallGraphicLeft= addVectorGraphic();
		wallGraphicLeft->displayStyle = DS_ARROW;
		wallGraphicLeft->color = glm::vec3(0,1,0);
		wallGraphicRight= addVectorGraphic();
		wallGraphicRight->displayStyle = DS_ARROW;
		wallGraphicRight->color = glm::vec3(0,1,0);

		resetBounce();
	
		collisionManager.init(&point,&wall);

		myDebugMenu.button("Reset Bounce", fastdelegate::MakeDelegate(this,&RestingCollisionGUI::resetBounce));
		myDebugMenu.button("Reset Rest", fastdelegate::MakeDelegate(this,&RestingCollisionGUI::resetRest));
		myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,0,0,false);
		myDebugMenu.watch("Plane Norm",wall.direction);
		myDebugMenu.watch("Pre Collision (Vel): ",preCollisionVel);
		myDebugMenu.watch("Pre Collision (Force): ",preCollisionForce);
		myDebugMenu.watch("Post Collision (Vel): ",postCollisionVel);
		myDebugMenu.watch("Post Collision (Force): ",postCollisionForce);
		myDebugMenu.edit("Gravity",gravity.y, 0, -10);
		myDebugMenu.edit("Restitution", collisionData.restitution, 0, 1);
		myDebugMenu.edit("Drag", point.drag, 0, 1);
		myDebugMenu.edit("Mass", point.mass,.1f,10);
	};
	void resetBounce() {
		point.pos = glm::vec3(-3,point.mass + 3,0);
		point.vel = glm::vec3(1,0,0);
	}
	void resetRest() {

		point.pos = glm::vec3(0,point.mass/2,0);
		point.vel = glm::vec3(0,0,0);
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		wall.direction = glm::normalize(wall.direction);

		if(mouseDragTimer.stop() > dt()*10) {
			//particle force update would go here
			point.totalForce += gravity;
			point.update(dt());
			this->preCollisionForce = point.totalForce;
			this->preCollisionVel = point.vel;
			collisionManager.update();
			if(collisionManager.hasCollided()) {
				collide();
			}
			this->postCollisionForce = point.totalForce;
			this->postCollisionVel = point.vel;

			point.clearForce();
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
		point.pos += dragDelta;

		collisionManager.update();

		redraw();
	}
	void redraw() {
		pointGraphic->pointSize = point.mass;
		syncVector(pointGraphic,point.pos);
		syncVector(vel,point.vel,point.pos);
		syncVector(mom,point.momentum,point.pos);
		glm::vec3 perpCCW = 1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
		glm::vec3 perpCW = -1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
		syncVector(wallGraphicLeft, perpCCW, wall.origin);
		syncVector(wallGraphicRight, perpCW, wall.origin);
	}
};