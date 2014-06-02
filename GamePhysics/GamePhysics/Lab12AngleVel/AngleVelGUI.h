#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <glm/gtx/perpendicular.hpp>

class AngleVelGUI : public PhysicsGUIBase {
	
	ParticleWorld theWorld;

	Particle point;
	VectorGraphic * pointGraphic;
	VectorGraphic * velGraphic;
	VectorGraphic * chainGraphic;
	VectorGraphic * radiusVector;

	bool onChain;

	glm::vec3 chainOrgin;

	float radius;
	float angleVel;

	glm::vec3 storedRadiusVector;
	
public:
	void init() {
		PhysicsGUIBase::init();

		radius = 3;
		angleVel = .5;
		onChain = true;

		theWorld.init(&point,1,nullptr,0);
		point.init(1,.5);
		chainOrgin = glm::vec3(1,1,1);

		pointGraphic = addVectorGraphic();
		chainGraphic = addVectorGraphic();
		chainGraphic->displayStyle = DS_SQUARE;
		chainGraphic->color = glm::vec3(0,1,0);
		velGraphic = addVectorGraphic();
		velGraphic->displayStyle = DS_ARROW;
		radiusVector = addVectorGraphic();
		radiusVector->displayStyle = DS_ARROW;
		radiusVector->color = glm::vec3(.1,.1,.1);

		myDebugMenu.edit("On Chain: ",onChain);
		myDebugMenu.edit("Chain\nPos",chainOrgin,-5,5);
		myDebugMenu.edit("Radius: ",radius,.0001,5);
		myDebugMenu.edit("Angle Vel: ",angleVel,0,10);
	};

	glm::vec3 getRad() {
		glm::vec3 diff = point.pos - chainOrgin;
		glm::vec3 norm = glm::normalize(diff);
		glm::vec3 expanded = radius * norm;
		return radius * glm::normalize(point.pos - chainOrgin);
	}

	void updateAnglur() {
		storedRadiusVector = getRad();

		if(onChain) {
			glm::vec3 rad = getRad();
			point.pos = chainOrgin + rad;
			glm::vec3 perp = glm::perp(rad,glm::vec3(0,0,1));
			perp = glm::vec3(-rad.y,rad.x,0);
			point.vel = perp * angleVel;
		}
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		theWorld.update(dt());

		updateAnglur();

		redraw();
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		if(vectorGraphicIndex == 1) {
			chainOrgin += dragDelta;
		}

		updateAnglur();

		redraw();
	}
	void redraw() {
		pointGraphic->pointSize = point.mass;
		sync(pointGraphic,point.pos);
		sync(velGraphic,point.vel,point.pos);
		sync(chainGraphic,chainOrgin);
		sync(radiusVector, storedRadiusVector, chainOrgin);
	}
};
