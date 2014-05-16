#pragma once

#include <PhysicsGui\GuiBase.h>
#include <Particle.h>
#include <DebugMenuManager.h>
#include "PhysicsGUIBase.h"

class SingleParticleGui: public PhysicsGUIBase {
protected:
	Particle myParticle;
	VectorGraphic * particalGraphic;
	VectorGraphic * velGraphic;
	VectorGraphic * momentumGraphic;
public:
	void init() {
		PhysicsGUIBase::init();
		particalGraphic = addVectorGraphic();
		particalGraphic->color = glm::vec3(.5,.5,.5);
		velGraphic = addVectorGraphic();
		velGraphic->displayStyle = DS_ARROW;
		velGraphic->color = glm::vec3(1,0,0);
		momentumGraphic = addVectorGraphic();
		momentumGraphic->displayStyle = DS_ARROW;
		momentumGraphic->color = glm::vec3(0,0,1);
	}
};