#pragma once

#include <Engine\Scene.h>
#include <ShapeGenerator.h>
#include <Engine\Tools\NUShapeEditor.h>

class Shadows : public Scene {
public:
	Shadows() : Scene("Shadows") {}


	PassInfo * shadowMap; //  has light cam
	Camera * sceneCam;

	glm::vec3 lightColor;
	float specPower;

	Renderable * lightRenderable;
	
	float depthPower;

	Renderable * setupRenderable(Renderable * toSetup) {
		toSetup->saveMatrixInfo("model2WorldTransform");
		toSetup->addUniformParameter("modelRotation",ParameterType::PT_MAT4,&toSetup->transformData.genRotMat()[0][0]);
		return toSetup;
	}


	void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(-6,5,-10),glm::vec3());
		sceneCam = &myCam;
		depthPower = 50;
		specPower = 100;
		lightColor = glm::vec3(.5,.5,.5);
		
		ShaderProgram * shadowShader = renderer->addShader("./../shaders/Shadow_V.glsl","./../shaders/Shadow_F.glsl");
		renderer->saveViewTransform(shadowShader,"viewTransform");
		

		//setup scene
		GeometryInfo * planeGeo = renderer->addGeometry(Neumont::ShapeGenerator::makePlane(2));
		GeometryInfo * objectGeo = renderer->addGeometry(NUShapeEditor::setRandomColor(NUShapeEditor::overrideColorWithTanNormals(Neumont::ShapeGenerator::makeTeapot(20,glm::mat4())),3));

		Renderable * mePlane = setupRenderable(renderer->addRenderable(planeGeo,shadowShader));
		mePlane->transformData.scale = glm::vec3(50,50,50);
		mePlane->transformData.position = glm::vec3(25,0,25);

		Renderable * meObject = setupRenderable(renderer->addRenderable(objectGeo,shadowShader));
		meObject->transformData.position.y = 1;
		meObject->transformData.rotation.x = -90;
		
		//save into passInfo
		shadowMap = renderer->addPassInfo(true);
		shadowMap->initTextures(renderer->width(),renderer->height());
		shadowMap->cam.enabled;
		shadowMap->cam.lookAt(glm::vec3(0,6,-10),glm::vec3());

		shadowShader->saveUniform("lightColor",ParameterType::PT_VEC3,&lightColor[0]);
		shadowShader->saveUniform("diffusePos",ParameterType::PT_VEC3,&shadowMap->cam.getPos()[0]);
		shadowShader->saveUniform("specPower",ParameterType::PT_FLOAT,&specPower);
		shadowShader->saveUniform("camPos",ParameterType::PT_VEC3,&myCam.getPos()[0]);
		shadowShader->saveUniform("shadowMap",ParameterType::PT_TEXTURE,&shadowMap->depthTexture);
		shadowShader->saveUniform("camLookAt",ParameterType::PT_MAT4,&shadowMap->cam.getWorld2View()[0][0]);
		renderer->savePerspectiveMat(shadowShader,"perspectiveMat");


		lightRenderable = renderer->addRenderable(renderer->addGeometry(Neumont::ShapeGenerator::makeSphere(20)),renderer->defaultShaders.passThroughColor);
		lightRenderable->saveMatrixInfo("model2WorldTransform");

		//setting up debugScreen

		ShaderProgram * screenSpaceHeros = renderer->addShader("./../shaders/ScreenSpace_V.glsl","./../shaders/ScreenSpace_F.glsl");
		renderer->saveViewTransform(screenSpaceHeros,"viewTransform");

		GeometryInfo * displayPlaneGeo = renderer->addGeometry(NUShapeEditor::rotate(NUShapeEditor::scaleToRange(Neumont::ShapeGenerator::makePlane(2),.3,.3,.3),90,0,0));
		Renderable * depthPlane = renderer->addRenderable(displayPlaneGeo,screenSpaceHeros, shadowMap->depthTexture);

		depthPlane->transformData.position = glm::vec3(1,.7,-1);
		depthPlane->saveMatrixInfo("meTransform");
		depthPlane->saveTexture("myTexture");
		depthPlane->addUniformParameter("power",depthPower);
		
		lightRenderable->visible = false;
		menu->edit("Disconnect Light",lightRenderable->visible);
	}
	void update(float dt) {
		if(!lightRenderable->visible) {
			shadowMap->cam = *sceneCam;
		}
		lightRenderable->transformData.position = shadowMap->cam.getPos();
		sceneCam->getWorld2View();
		shadowMap->cam.getWorld2View();
	}
};