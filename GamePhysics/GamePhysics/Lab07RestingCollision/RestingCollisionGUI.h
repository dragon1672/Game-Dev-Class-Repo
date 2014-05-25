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
	VectorGraphic * collideVel;
	Ray wall;
	VectorGraphic * wallGraphic;

	float preCollisionForce;
	float postCollisionForce;
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
		collisionData.restitution = 1;

		collisionData.particle[0] = &point;
		collisionData.particle[1] = nullptr;
		point.init(.95,1);
		pointGraphic = addVectorGraphic();
		pointGraphic->color = glm::vec3(1,0,0);
		mom = addVectorGraphic();
		mom->displayStyle = DS_ARROW;
		mom->color = glm::vec3(0,0,1);
		collideVel = addVectorGraphic();
		collideVel->displayStyle = DS_ARROW;
		collideVel->color = glm::vec3(1,0,0);
		vel= addVectorGraphic();
		vel->displayStyle = DS_ARROW;
		vel->color = glm::vec3(0,1,0);

		resetBounce();
	
		collisionManager.init(&point,&wall);

		myDebugMenu.button("Reset Bounce", fastdelegate::MakeDelegate(this,&RestingCollisionGUI::resetBounce));
		myDebugMenu.button("Reset Rest", fastdelegate::MakeDelegate(this,&RestingCollisionGUI::resetRest));
		myDebugMenu.edit("Plane Orgin",wall.origin,5,5,0);
		myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,0,0);
		myDebugMenu.watch("Pre Collision Force: ",preCollisionForce);
		myDebugMenu.watch("Post Collision Force: ",postCollisionForce);
		myDebugMenu.edit("Gravity",gravity, 10,10,0);
		myDebugMenu.edit("Restitution", collisionData.restitution, 0, 1);
	};
	void resetBounce() {
		point.pos = glm::vec3(-3,3,0);
		point.vel = glm::vec3(1,0,0);
	}
	void resetRest() {
		point.pos = glm::vec3(0,.5,0);
		point.vel = glm::vec3(0,0,0);
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		wall.direction = glm::normalize(wall.direction);

		if(mouseDragTimer.stop() > dt()*10) {
			//particle force update would go here
			point.totalForce += gravity;
			this->preCollisionForce = glm::dot(point.totalForce,point.totalForce);
			collisionManager.update();
			if(collisionManager.hasCollided()) {
				collide();
			}
			this->postCollisionForce = glm::dot(point.totalForce,point.totalForce);

			point.update(dt());
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
		syncVector(collideVel,collisionManager.vel,point.pos);
	}
};