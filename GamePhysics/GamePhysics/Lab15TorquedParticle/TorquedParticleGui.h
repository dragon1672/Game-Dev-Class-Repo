#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <glm/gtx/perpendicular.hpp>
#include <MyRandom.h>
#include <glm/gtx/rotate_vector.hpp>

#include <RidgidBody.h>
#include <RigidSpringForce.h>

class TorquedParticleGui : public PhysicsGUIBase {
	
	struct Line {
		RidgidBody * src;
		glm::vec3 offset;
		VectorGraphic * theLine;
		glm::vec3 syncPos() {
			return src->core.pos + glm::rotate(offset,glm::degrees(src->rotation),glm::vec3(0,0,-1));
		}
		glm::vec3 syncVec(glm::vec3& springPos) {
			return springPos - syncPos();
		}
	};
	
	struct {
		RidgidBody point;
		VectorGraphic * pointGraphic;
		VectorGraphic * angleVelGraphic;
		
		Line meSpring;
		/*
			RidgidBody * src;
			glm::vec3 offset;
			VectorGraphic * theLine;
		//*/
	} ridgidBody;
	
	glm::vec3 mousePos;

	RigidSpringForce mySprings;
	GravityForceGenerator myGrav;

	void initGraphic(VectorGraphic** leGraphic, glm::vec3& col, DisplayStyle type = DS_ARROW) {
		(*leGraphic)  = addVectorGraphic();
		(*leGraphic) -> displayStyle = type;
		(*leGraphic) -> color = col;
	}
public:
	void init() {
		PhysicsGUIBase::init(false,false);

		myGrav.dir = glm::vec3(0,-10,0);
		mySprings.init(25,2);

		reset();

		initGraphic(&ridgidBody.pointGraphic, glm::vec3(0,0,1), DisplayStyle::DS_SQUARE);
		
		initGraphic(&ridgidBody.angleVelGraphic, glm::vec3(0,0,0));

		ridgidBody.meSpring.src = &ridgidBody.point;
		ridgidBody.meSpring.offset = glm::vec3(Random::randomSign() * ridgidBody.point.core.mass/2,Random::randomSign() * ridgidBody.point.core.mass/2,0);
		mySprings.addSpring(ridgidBody.point,ridgidBody.meSpring.offset,mousePos);
		initGraphic(&ridgidBody.meSpring.theLine, glm::vec3(), DisplayStyle::DS_LINE);

		myDebugMenu.button("Reset",fastdelegate::MakeDelegate(this,&TorquedParticleGui::reset));
		myDebugMenu.edit("Drag",ridgidBody.point.core.drag, 0, 1);
		myDebugMenu.edit("SpringStiff",mySprings.springConstent,0,100);
		myDebugMenu.watch("pos",ridgidBody.point.core.pos);
	}
	void reset() {
		ridgidBody.point.core.init(.8,1);
		ridgidBody.point.core.pos = glm::vec3();
		ridgidBody.point.core.vel = glm::vec3();

		ridgidBody.point.angleVel = 0;
		ridgidBody.point.rotation = 0;
		ridgidBody.point.totalInertia = 1;
		ridgidBody.point.totalTorque = glm::vec3();
	}

	void mouseSpringUpdate() {
		if(GetAsyncKeyState(VK_RBUTTON)) {
			mousePos = getMousePosition();
		}
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		mouseSpringUpdate();
		
		mySprings.updateForce(&ridgidBody.point);
		myGrav.updateForce(&ridgidBody.point.core);

		ridgidBody.point.update(dt());

		redraw();
	}
	void redraw() {
		ridgidBody.pointGraphic->pointSize = ridgidBody.point.core.mass;
		ridgidBody.pointGraphic->rotation = ridgidBody.point.rotation;
		sync(ridgidBody.pointGraphic,ridgidBody.point.core.pos);
		//sync(ridgidBody.angleVelGraphic,ridgidBody.point.vel,ridgidBody.point.pos);
		sync(ridgidBody.meSpring.theLine,ridgidBody.meSpring.syncVec(mousePos),ridgidBody.meSpring.syncPos());
	}
};