#pragma once

#include <Engine\BasicGui.h>
#include <ShapeGenerator.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\NUShapeEditor.h> // VERY handy tools for editing NU shapes
#include <Engine\Tools\Random\Glm.h> // includes all random from myRandom + glm randomness
#include <Engine\Tools\BinaryToShapeLoader.h>
#include <ctime>

#include <glm\gtx\transform.hpp>

class NormalMaps : public WidgetRenderer {
public:
	Renderable * mePlane;
	Renderable * lightSrcRenderable;
	int normalMap;

	glm::vec3 lightSrc;
	glm::vec3 lightColor;
	float specPower;

	bool whiteAsTexture;

	void init() {
		myCam.setPos(glm::vec3(0,.1,10),glm::vec3(0,0,-.5));

		specPower = 100;
		lightColor = glm::vec3(1,1,1);
		lightSrc = glm::vec3(0,4,10);

		whiteAsTexture = false;

		auto meGeo =  addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("./../models/plane.bin"),5),GL_TRIANGLES);
		auto cameraGeo = addGeometry(Neumont::ShapeGenerator::makeSphere(50),GL_TRIANGLES);

		lightSrcRenderable = addRenderable(cameraGeo,mainShader,-1);
		lightSrcRenderable->saveWhereMat("model2WorldTransform");

		ShaderProgram * meShader = addShader("./../shaders/basicNormal_V.glsl","./../shaders/basicNormal_F.glsl"); // for clock, clock face
		saveViewTransform(meShader,"viewTransform");
		meShader->saveUniform("diffusePos",   ParameterType::PT_VEC3, &lightSrc[0]         );
		meShader->saveUniform("lightColor", ParameterType::PT_VEC3, &lightColor[0]         );
		meShader->saveUniform("camPos",     ParameterType::PT_VEC3, &myCam.getPos()[0]     );
		meShader->saveUniform("specPower",  ParameterType::PT_FLOAT, &specPower            );
		meShader->saveUniform("whiteAsTexture", ParameterType::PT_BOOLEAN, &whiteAsTexture );
		
		mePlane = addRenderable(meGeo,meShader,addTexture("./../textures/basicNormal.png"));
		mePlane->saveTexture("normalMap");
		mePlane->saveWhereMat("model2WorldTransform");
		mePlane->whereMat = glm::rotate(90.0f,glm::vec3(1,0,0));

		menu->edit("lightPosition",lightSrc,-15,15);
		menu->edit("lightColor",lightColor,0,1);
		menu->edit("specPower",specPower,3,100);
		menu->edit("showLightSrc",lightSrcRenderable->visible);
		menu->edit("whiteAsTexture",whiteAsTexture);
	}
	
	void nextFrame(float dt) {
		lightSrcRenderable -> whereMat = glm::translate(lightSrc) * glm::scale(glm::vec3(.2,.2,.2));
	}
};