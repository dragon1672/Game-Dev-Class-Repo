#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <glm/gtx/perpendicular.hpp>

class AngleVelGUI : public PhysicsGUIBase {
	
	ParticleWorld theWorld;

	Particle point;
	VectorGraphic * pointGraphic;
	VectorGraphic * velGraphic;
	VectorGraphic * chainGraphic;
	VectorGraphic * radiusVector;

	bool onChain;

	glm::vec3 chainOrgin;

	float radius;
	float angleVel;

	glm::vec3 storedRadiusVector;
	
public:
	void init();
	glm::vec3 getRad();
	void updateAnglur();
	void newFrame();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
	void redraw();
};
