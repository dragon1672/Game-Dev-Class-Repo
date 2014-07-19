#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness

#include <glm\gtx\transform.hpp>

class DebugMenuDemo : public WidgetRenderer {
public:
	static const int rotSpeedRange = 100;
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;

	glm::vec3 blendColor;
	char * myString;

	float updateRate;
	float currentTime;

	Renderable * meRenderable;
	void init() {
		myCam.setPos(glm::vec3(0,.1,0),glm::vec3(0,0,.5));

		updateRate = 2;
		currentTime = 0;
		auto meShader = addShader("../shaders/vert.glsl","../shaders/frag.glsl");
		saveViewTransform(meShader,"viewTransform");

		blendColor = Random::glmRand::randomFloatVectorInBox(1,1,1);
		
		myString = "pie is good";
		//menu->watch("Demo:",myStrin,"Stats");
		myString = "Pie is really good (edited)";

		menu->watch("Blend: ",blendColor,"Stats");
		menu->watch("Rotation: ",rotation,"Stats");
		menu->watch("RotationSpeed: ",rotationSpeed,"Stats");
		menu->edit("BlendColor: ",blendColor,0,1,0,1,0,1,true,"Editor");
		menu->edit("updateRate: ",updateRate,0,5,true,"Editor");
		menu->watch("Current Time: ",currentTime,"Editor");
		menu->edit("Blend: ",blendColor,0,1,0,1,0,1,true,"Editor");
		menu->edit("RotationSpeed: ",rotationSpeed,rotSpeedRange,rotSpeedRange,rotSpeedRange,true,"Editor");

		auto tempGeo = addGeometry(NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeSphere(20)),GL_TRIANGLES);
		meRenderable = addRenderable(tempGeo,meShader,-1);
		meRenderable->saveWhereMat("model2WorldTransform"); // really just a call to addUniformPram
		meRenderable->addUniformParameter("blendColor",ParameterType::PT_VEC3,&blendColor[0]);

	}
	void nextFrame(float dt) {
		currentTime += dt;
		if(currentTime > updateRate) {
			currentTime = 0;
			blendColor = Random::glmRand::randomFloatVectorInBox(1,1,1);
			rotationSpeed = Random::glmRand::randomFloatVectorInBoxRanged(rotSpeedRange,rotSpeedRange,rotSpeedRange);
		}

		//just edit the where matrix for renderables
		rotation += rotationSpeed * dt;
		meRenderable->whereMat = glm::rotate(rotation.x,glm::vec3(1,0,0))
							  *= glm::rotate(rotation.y,glm::vec3(0,1,0))
							  *= glm::rotate(rotation.z,glm::vec3(0,0,1));
	}
};