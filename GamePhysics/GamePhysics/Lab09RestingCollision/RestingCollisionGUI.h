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
	void init();
	void resetBounce();
	void resetRest();
	void newFrame();
	void collide();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
	void redraw();
};