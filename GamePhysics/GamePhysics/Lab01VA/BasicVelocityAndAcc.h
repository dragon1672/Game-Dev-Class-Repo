#pragma once

#include "../SingleParticleGui.h"

class BasicVelocityAndAcc : public SingleParticleGui {
public:
	void init() {
		SingleParticleGui::init();
	}
	void newFrame() {
		float acc = 1;
		vel += acc * dt() * getUserDirection();
		pos += vel * dt();
		sync(particalGraphic,pos);
		sync(velGraphic,vel,pos);
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		pos += dragDelta;
		vel += dragDelta / 4.0f;
		sync(particalGraphic,pos);
		sync(velGraphic,vel,pos);
	}
};