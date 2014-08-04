#pragma once

#include <Engine\Scene.h>
#include <ShapeGenerator.h>
#include <noise\noise.h>
#include <Engine\Tools\NUShapeEditor.h>

class UsingNoise : public Scene {
public:
	UsingNoise() : Scene("Using Noise") {}

	struct {
		Renderable * renderable;
		int noiseTexture;
		float percent;
		float discardThreshold;
		glm::vec3 rotAcc;
	} bears[4];

	struct {
		Renderable * Teapot;
		int noiseTexture;
		glm::vec2 uvOffset;
		float magnitude;
	} teapot;

	float colorPower;
	float depthPower;

	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu);
	void update(float dt);
	int genTexture(Renderer * renderer, int zVal = 20, bool seemless = true);
};