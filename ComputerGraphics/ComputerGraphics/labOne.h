#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h>

#include <glm\gtx\transform.hpp>

class LabOne : public WidgetRenderer {
public:
	static const int skyboxScale = 4;
	static const int cloudOffset = 1;
	float skyboxRotation;
	float cloudRotation;

	int alphaTexture;
	int mainTexture;
	int grassTexture;
	int skyTexture;

	Renderable * skyBoxRenderable;
	Renderable * cloudRenderable;
	Renderable * planeRenderable;
	void init() {
		myCam.setPos(glm::vec3(0,.1,0),glm::vec3(0,0,.5));

		skyboxRotation = cloudRotation = 0;
		auto meShader = addShader("../shaders/alphaV.glsl","../shaders/alphaF.glsl");
		saveViewTransform(meShader,"viewTransform");
		mainShader = addShader("../shaders/passV.glsl","../shaders/passF.glsl");
		saveViewTransform(mainShader,"viewTransform");

		alphaTexture = addTexture("./../textures/Alpha.png");
		mainTexture  = addTexture("./../textures/Alpha_mainTexture.png");
		grassTexture = addTexture("./../textures/Grass.png");
		skyTexture = addTexture("./../textures/nightSky.png");


		

		auto skyBoxGeo = addGeometry(NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeSphere(20)),GL_TRIANGLES);
		cloudRenderable = addRenderable(skyBoxGeo,meShader,mainTexture);
		cloudRenderable->saveWhereMat("model2WorldTransform");
		cloudRenderable->saveTexture("myTexture");
		cloudRenderable->addUniformParameter("myAlpha",ParameterType::PT_TEXTURE,&alphaTexture);

		skyBoxRenderable = addRenderable(skyBoxGeo,mainShader,skyTexture);
		skyBoxRenderable->saveWhereMat("model2WorldTransform");
		skyBoxRenderable->saveTexture("myTexture");

		auto planeGeo = addGeometry(Neumont::ShapeGenerator::makePlane(10),GL_TRIANGLES);
		planeRenderable = addRenderable(planeGeo,mainShader,grassTexture);
		planeRenderable->saveWhereMat("model2WorldTransform");
		planeRenderable->saveTexture("myTexture");
	}
	void nextFrame(float dt) {
		cloudRotation -= 10 * dt;
		skyboxRotation += 3 * dt;
		cloudRenderable->whereMat = glm::rotate(cloudRotation,glm::vec3(0,0,1)) * glm::scale(glm::vec3(skyboxScale,skyboxScale,skyboxScale));
		skyBoxRenderable->whereMat = glm::rotate(skyboxRotation,glm::vec3(0,0,1)) * glm::scale(glm::vec3(skyboxScale+cloudOffset,skyboxScale+cloudOffset,skyboxScale + cloudOffset));
		planeRenderable->whereMat = glm::scale(glm::vec3(1,1,1));
		//*skyBoxMatrix = glm::rotate(skyboxRotation,glm::vec3(0,0,1)) * glm::scale(glm::vec3(skyboxScale,skyboxScale,skyboxScale));
	}
};