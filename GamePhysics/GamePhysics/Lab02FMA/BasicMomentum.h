#pragma once

#include "../SingleParticleGui.h"

class BasicMomentum : public SingleParticleGui {
	bool conserveMomentum;
public:
	void init() {
		SingleParticleGui::init();
		myParticle.init(1,1);
		conserveMomentum=false;

		//debug menus
		myDebugMenu.slideFloat("Mass",myParticle.mass,.01f,10);
		myDebugMenu.slideFloat("Drag",myParticle.drag,.01f,1);
		myDebugMenu.watchVector("Momentum",myParticle.momentum);
		myDebugMenu.watchVector("Velocity",myParticle.vel);
		myDebugMenu.watchVector("Position",myParticle.pos);
		myDebugMenu.toggleBool("Conserve Momentum ?",conserveMomentum);
	}
	void newFrame() {
		SingleParticleGui::newFrame();

		glm::vec3& vel = myParticle.vel;
		glm::vec3& pos = myParticle.pos;
		glm::vec3& momentum = myParticle.momentum;
		float& mass = myParticle.mass;
		float& drag = myParticle.drag;

		if(conserveMomentum) {
			vel = momentum / mass;
		}
		vel += getUserDirection() * 1.0f * dt();

		vel *= drag;
		momentum = vel * mass;
		pos += vel * dt();

		particalGraphic->pointSize = myParticle.mass;


		sync(particalGraphic,myParticle.pos);
		sync(velGraphic,myParticle.vel,myParticle.pos);
		sync(momentumGraphic,myParticle.momentum,myParticle.pos);
	}
};