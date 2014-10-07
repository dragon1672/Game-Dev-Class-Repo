#pragma once

#include <Engine\Systems\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\Systems\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <ctime>

#include <glm\gtx\transform.hpp>

class Testing : public WidgetRenderer {
public:
	float layer;
	glm::vec3 color;
	float updateRate;

	void init();
	
	void nextFrame(float dt);
};