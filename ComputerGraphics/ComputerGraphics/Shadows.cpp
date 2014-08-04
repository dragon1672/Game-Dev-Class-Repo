#include "Shadows.h"

Renderable * Shadows::setupRenderable(Renderable * toSetup) {
	toSetup->saveMatrixInfo("model2WorldTransform");
	toSetup->addUniformParameter("modelRotation",ParameterType::PT_MAT4,&toSetup->transformData.genRotMat()[0][0]);
	return toSetup;
}
void Shadows::init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
	myCam.lookAt(glm::vec3(-30,20,0),glm::vec3());
	viewCamera = &myCam;
	sceneCam = *viewCamera;
	depthPower = 50;
	specPower = 100;
	thres = .0005f;
	lightColor = glm::vec3(.5,.5,.5);

	biasMatrix = glm::mat4 (
							0.5, 0.0, 0.0, 0.0,
							0.0, 0.5, 0.0, 0.0,
							0.0, 0.0, 0.5, 0.0,
							0.5, 0.5, 0.5, 1.0
						);
		
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
	meObject->transformData.position.z = -4;
	meObject->transformData.setScale(4);
	meObject->transformData.rotation.x = -90;
		
	//save into passInfo
	shadowMap = renderer->addPassInfo(true);
	shadowMap->initTextures(renderer->width(),renderer->height());
	shadowMap->cam.enabled = true;
	shadowMap->cam.lookAt(glm::vec3(0,20,-40),glm::vec3());

	shadowShader->saveUniform("shadowMap",ParameterType::PT_TEXTURE, &shadowMap->depthTexture);
	shadowShader->saveUniform("lightColor", lightColor);
	shadowShader->saveUniform("diffusePos", shadowMap->cam.getPos());
	shadowShader->saveUniform("specPower",  specPower);
	shadowShader->saveUniform("camPos",     myCam.getPos());
	shadowShader->saveUniform("camLookAt",  shadowMap->cam.getWorld2View());
	shadowShader->saveUniform("biasMatrix", biasMatrix);
	shadowShader->saveUniform("thres", thres);
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
		
	menu->setSliderGranularity(100000);
	menu->edit("Set Cam As Light",camIsLight);
	menu->edit("thres",thres,0,.001);
	menu->edit("nearPlane",renderer->nearPlane,0,.1);
	menu->edit("farPlane",renderer->farPlane,10,100);
}
void Shadows::update(float dt) {
	if(camWasLight != camIsLight) {

		if(camIsLight) {
			viewCamera->setPos(shadowMap->cam.getPos(),shadowMap->cam.getViewDir());
		} else {
			viewCamera->setPos(sceneCam.getPos(),sceneCam.getViewDir());
		}
	} else {
		if(camIsLight) {
			shadowMap->cam = *viewCamera;
		} else {
			sceneCam = *viewCamera;
		}
	}
	camWasLight = camIsLight;
	lightRenderable->visible = !camIsLight;	
	lightRenderable->transformData.position = shadowMap->cam.getPos();
	sceneCam.getWorld2View();
	shadowMap->cam.getWorld2View();
}