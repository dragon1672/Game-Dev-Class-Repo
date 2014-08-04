#pragma once

#include <Engine\Scene.h>
#include <Engine\Tools\NUShapeEditor.h>
#include <ShapeGenerator.h>
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <Engine\Tools\Random\Glm.h>
#include <noise\noise.h>

class PassInfoDemo : public Scene {
public:
	PassInfoDemo() : Scene("Pass Info Demo") {}

	struct {
		Renderable * renderable;
		int noiseTexture;
		float percent;
		float discardThreshold;
	} bears[4];

	struct {
		Renderable * Teapot;
		int noiseTexture;
		glm::vec2 uvOffset;
		float magnitude;
	} teapot;

	PassInfo * meEpicTexture;


	void addToFakeOutput(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu);

	virtual void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu);
	virtual void update(float dt);

	int genTexture(Renderer * renderer, int zVal = 20, bool seemless = true);
};