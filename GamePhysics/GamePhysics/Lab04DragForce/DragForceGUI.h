#pragma once

#include "../SingleParticleGui.h"
#include <ParticleForceRegistry.h>
#include <DragForceGenerator.h>
#include <GravityForceGenerator.h>
#include <VectorBoundForceGenerator.h>

class DragForceGUI : public SingleParticleGui {
	DragForceGenerator myDrag;
	ParticleForceRegistry forceManager;
	VectorGraphic * lowDragGraphic;
	VectorGraphic * highDragGraphic;
	glm::vec3 keyboardInput;
	GravityForceGenerator myGrav;
	VectorBoundForceGenerator myKeyboard;
	bool enableGrav;
	bool enableGrav_last;
	bool enableKey;
	bool enableKey_last;
	bool enableDrag;
	bool enableDrag_last;
public:
	void init();
	void newFrame();
private:
	void updateForces();
	void resetParticle();
};