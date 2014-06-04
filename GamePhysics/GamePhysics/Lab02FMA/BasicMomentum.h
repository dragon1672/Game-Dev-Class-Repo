#pragma once

#include "../SingleParticleGui.h"

class BasicMomentum : public SingleParticleGui {
	bool conserveMomentum;
public:
	void init();
	void newFrame();
};