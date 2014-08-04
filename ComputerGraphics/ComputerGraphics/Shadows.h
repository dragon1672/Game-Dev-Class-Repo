#pragma once

#include <Engine\Scene.h>
#include <ShapeGenerator.h>
#include <Engine\Tools\NUShapeEditor.h>

class Shadows : public Scene {
public:
	Shadows() : Scene("Shadows") {}


	PassInfo * shadowMap; //  has light cam
	Camera * viewCamera, sceneCam;
	bool camIsLight, camWasLight;

	glm::mat4 biasMatrix;

	glm::vec3 lightColor;
	float specPower;

	Renderable * lightRenderable;

	float thres;
	
	float depthPower;

	Renderable * setupRenderable(Renderable * toSetup);
	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu);
	void update(float dt);
};