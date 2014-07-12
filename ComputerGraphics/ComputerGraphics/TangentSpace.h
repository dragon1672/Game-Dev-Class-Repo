#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <ctime>

#include <glm\gtx\transform.hpp>

class TangentSpace : public WidgetRenderer {
public:
	Renderable * meCube;
	glm::mat4 cubeRotation;
	Renderable * lightSrcRenderable;
	int normalMap;

	glm::vec3 lightColor;
	float specPower;

	bool whiteAsTexture;

	void init();
	
	void nextFrame(float dt);
};