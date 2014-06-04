#pragma once

#include <PhysicsGui/GuiBase.h>
#include <Particle.h>
#include <DebugMenuManager.h>

class PhysicsGUIBase : public GuiBase {
protected:
	DebugMenuManager myDebugMenu;
public:
	void init(bool threeD = false, bool autoStep = true);
	void newFrame();
	glm::vec3 getUserDirection();
	void syncVector(VectorGraphic * toSync, glm::vec3 vec, glm::vec3 base=glm::vec3());
};