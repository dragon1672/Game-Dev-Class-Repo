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
	void init();
	void syncBaseVectors();
};