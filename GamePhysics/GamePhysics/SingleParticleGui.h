#pragma once

#include <PhysicsGui\GuiBase.h>
#include <Particle.h>
#include <DebugMenuManager.h>

class SingleParticleGui: public GuiBase {
protected:
	DebugMenuManager myDebugMenu;
	Particle myParticle;
	VectorGraphic * particalGraphic;
	VectorGraphic * velGraphic;
	VectorGraphic * momentumGraphic;
public:
	void init() {
		GuiBase::initialize(false,true);
		particalGraphic = addVectorGraphic();
		velGraphic = addVectorGraphic();
		velGraphic->displayStyle = DS_ARROW;
		velGraphic->r=255;
		momentumGraphic = addVectorGraphic();
		momentumGraphic->displayStyle = DS_ARROW;
		momentumGraphic->g=255;
		momentumGraphic->b=0;
		
		
		myDebugMenu.init();
		debugLayout->addWidget(&myDebugMenu);
	}
	void newFrame() {
		myDebugMenu.update();
	}
	glm::vec3 getUserDirection() {
		glm::vec3 ret;
		int count = 0;
		if(isKeyDown("up"))    { ret += glm::vec3( 0, 1, 0); count++; }
		if(isKeyDown("left"))  { ret += glm::vec3(-1, 0, 0); count++; }
		if(isKeyDown("right")) { ret += glm::vec3( 1, 0, 0); count++; }
		if(isKeyDown("down"))  { ret += glm::vec3( 0,-1, 0); count++; }
		ret = (count>1)? glm::normalize(ret) : ret;
		return ret;
	}
};