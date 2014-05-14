#pragma once

#include "../SingleParticleGui.h"

class BasicMomentum : public SingleParticleGui {
public:
	void init() {
		SingleParticleGui::init();
		myParticle.init(1,.5,1);
		myDebugMenu.slideFloat("Mass",myParticle.mass,.01,10);
		myDebugMenu.slideFloat("Drag",myParticle.drag,.01,1);
		myDebugMenu.watchVector("Momentum",myParticle.momentum);
		myDebugMenu.watchVector("Velocity",myParticle.vel);
		myDebugMenu.watchVector("Position",myParticle.pos);
		myDebugMenu.toggleBool("Conserve Momentum ?",myParticle.conserveMomentum);
	}
	void newFrame() {
		SingleParticleGui::newFrame();
		myParticle.update(getUserDirection(),dt());
		particalGraphic->pointSize = myParticle.mass;
		sync(particalGraphic,myParticle.pos);
		sync(velGraphic,myParticle.vel,myParticle.pos);
		sync(momentumGraphic,myParticle.momentum,myParticle.pos);
	}
};