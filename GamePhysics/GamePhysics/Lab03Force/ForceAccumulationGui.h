#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <VectorBoundForceGenerator.h>
#include <GravityForceGenerator.h>

class ForceAccumulationGui : public PhysicsGUIBase {
protected:
	Particle one;
	Particle two;
	Particle thr;
	VectorGraphic * oneGraphic;
	VectorGraphic * twoGraphic;
	VectorGraphic * thrGraphic;
	glm::vec3 keyboardInput;
	ParticleForceRegistry forceManager;
	VectorBoundForceGenerator keyboardForce;
	GravityForceGenerator gravForce;
public:
	void init() {
		PhysicsGUIBase::init();
		setupGraphics();

		one.init(1);
		one.pos = glm::vec3(-2,0,0);
		two.init(1);
		thr.init(1);
		thr.pos = glm::vec3(2,0,0);

		keyboardForce.init(keyboardInput);
		gravForce.dir = glm::vec3(0,-9.81,0);
		forceManager.add(&one,&gravForce);
		forceManager.add(&two,&gravForce);
		forceManager.add(&two,&keyboardForce);
		forceManager.add(&thr,&keyboardForce);

		myDebugMenu.watchVector("One",one.pos);
		myDebugMenu.watchVector("two",two.pos);
		myDebugMenu.watchVector("thr",thr.pos);
	}
	void setupGraphics() {
		oneGraphic = addVectorGraphic();
		twoGraphic = addVectorGraphic();
		thrGraphic = addVectorGraphic();
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		keyboardInput = getUserDirection() * 20.0f;

		forceManager.updateForces();

		one.update(dt());
		two.update(dt());
		thr.update(dt());


		oneGraphic->pointSize = one.mass;
		twoGraphic->pointSize = two.mass;
		thrGraphic->pointSize = thr.mass;
		sync(oneGraphic,one.pos);
		sync(twoGraphic,two.pos);
		sync(thrGraphic,thr.pos);
	}
};