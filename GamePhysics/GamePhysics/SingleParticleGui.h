#pragma once

#include <PhysicsGui\GuiBase.h>
#include <Particle.h>
#include <DebugMenuManager.h>
#include "PhysicsGUIBase.h"

class SingleParticleGui: public PhysicsGUIBase {
protected:
	DebugMenuManager myDebugMenu;
	Particle myParticle;
	VectorGraphic * particalGraphic;
	VectorGraphic * velGraphic;
	VectorGraphic * momentumGraphic;
public:
	void init() {
		PhysicsGUIBase::initialize(false,true);
		particalGraphic = addVectorGraphic();
		particalGraphic->r = 150;
		particalGraphic->g = 150;
		particalGraphic->b = 150;
		velGraphic = addVectorGraphic();
		velGraphic->displayStyle = DS_ARROW;
		velGraphic->r=255;
		velGraphic->b = 0;
		momentumGraphic = addVectorGraphic();
		momentumGraphic->displayStyle = DS_ARROW;
		momentumGraphic->b=255;
	}
};