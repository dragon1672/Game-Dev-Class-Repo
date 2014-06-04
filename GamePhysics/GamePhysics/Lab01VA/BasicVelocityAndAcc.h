#pragma once

#include "../SingleParticleGui.h"

class BasicVelocityAndAcc : public SingleParticleGui {
public:
	void init();
	void newFrame();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
};