#pragma once

#include <Engine\Scene.h>
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <Engine\Tools\Random\Glm.h>
#include <ShapeGenerator.h>

class CubeMap : public Scene {
public:
	CubeMap() : Scene("Cube Map") {}

	uint worldTexture;

	std::vector<GeometryInfo *> geos;
	int geoID;

	std::vector<uint> textures;
	int currentTextureID;

	Renderable * world;
	Renderable * meObject;
	glm::vec3 angleVel;

	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu);
	void update(float dt);
};