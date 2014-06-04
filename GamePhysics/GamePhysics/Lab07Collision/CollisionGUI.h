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
	VectorGraphic * systemMomGraphic;
	int numOfNodes;
	glm::vec3 systemMom;
	float totalKineticEnergy;
	ParticleContact collisionData;
	CollisionMassCircles collisionManager;
public:
	void init();
	void factoryReset();
	void reset();
	void reset2D();
	void newFrame();
	void collide();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
	void redraw();
};