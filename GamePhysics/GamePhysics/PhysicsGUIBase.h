#pragma once

#include <PhysicsGui/GuiBase.h>
#include <Particle.h>
#include <DebugMenuManager.h>

class PhysicsGUIBase : public GuiBase {
protected:
	DebugMenuManager myDebugMenu;
public:
	void init(bool threeD = false, bool autoStep = true) {
		GuiBase::initialize(threeD,autoStep);
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
	void syncVector(VectorGraphic * toSync, glm::vec3 vec, glm::vec3 base=glm::vec3()) {
		static float maxSize = 0;
		float currentLength = glm::dot(vec,vec);
		maxSize = maxSize < currentLength ? currentLength : maxSize;
		//WHAT IS GOING ON?!?!
		base.z = -1;//Random::randomFloat();//currentLength / maxSize;
		sync(toSync,vec,base);
	}
};