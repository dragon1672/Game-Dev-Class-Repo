#pragma once

#include <PhysicsGui\GuiBase.h>

class SingleParticleGui: public GuiBase {
protected:
	glm::vec3 pos;
	glm::vec3 vel;
	VectorGraphic * particalGraphic;
	VectorGraphic * velGraphic;

public:
	void init() {
		GuiBase::initialize(false,true);
		particalGraphic = addVectorGraphic();
		velGraphic = addVectorGraphic();
		velGraphic->displayStyle = DS_ARROW;
		velGraphic->r=255;
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