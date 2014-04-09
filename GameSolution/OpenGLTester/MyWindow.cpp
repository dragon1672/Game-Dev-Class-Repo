#include <GL\glew.h>
#include "MyWindow.h"
#include "MyRandom.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt/qdebug.h>

#include <ShapeGenerator.h>
#include "BinaryToShapeLoader.h"
#include "NUShapeEditor.h"

#include "SingleKeyManager.h"


using glm::vec3;
using glm::mat4x4;

Neumont::ShapeData singleShape;

const int numOfShapesToMake = 50;


void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&myRender, &viewTransform[0][0]);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");

	sendDataToHardWare();

	setMouseTracking(true);
	
	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}

void MyWindow::init(DebugMenuManager * debugMenu) {
	this->debugMenu = debugMenu;
	//setting defaults
	enableOverrideColor = true;
	displayLightEntity = true;
	myCam.setPos(vec3(17,3.7f,-15),vec3(-50,-13,85));
	overrideColor = vec3(1,1,1);
	ambientLight = vec3(.1,.1,.1);
	diffuseLight = vec3(1,1,1);
	diffusePos = vec3(0,10,0);
	diffuseInFrag = true;
	specColor = vec3(1,0,1);
	specPower = 50;

	objectsMoving = true;
	enableTexture = true;
	enableLighting = true;
	registerInDebugMenu();
}
void MyWindow::registerInDebugMenu() {
	debugMenu->toggleBool("Display Light Source",displayLightEntity);
	debugMenu->slideVector("Diffuse Pos", diffusePos,-1.5*range,1.5*range);
	debugMenu->slideVector("Overriding Color",overrideColor,0,1);
	debugMenu->slideVector("Spec Color",specColor,0,1);
	debugMenu->slideFloat("Spec Power",specPower,25,1000);

	debugMenu->toggleBool("Lighting in Fragment Shader",diffuseInFrag);
	debugMenu->toggleBool("Override Default Colors",enableOverrideColor);
	debugMenu->toggleBool("Allow Objects To Move",objectsMoving);
	debugMenu->toggleBool("Enable Textures",enableTexture);
	debugMenu->toggleBool("Enable Lighting",enableLighting);
	debugMenu->toggleBool("Display Light Entity",displayLightEntity);
	debugMenu->watchVector("LightRot[0]",lightSource.rotation[0]);
	debugMenu->watchVector("LightRot[1]",lightSource.rotation[1]);
	debugMenu->watchVector("LightRot[2]",lightSource.rotation[2]);
	debugMenu->watchFloat("Current Spec",specPower);
}

int sendTextures(Renderer& myRender) {
	int numOfTextures;
	numOfTextures = myRender.addTexture("\\..\\Textures\\black eyes.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\blueLInes.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\bsod.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\color bands.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\ComfyChair_Diffuse2.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\face hands.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\green matrix.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\jamie Avatar.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\obama bill.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\Rust.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\slaceRocks.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\Smile.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\ToonTeddyBear.png");
	numOfTextures = myRender.addTexture("\\..\\Textures\\wood2.png");
	return numOfTextures;
}

void MyWindow::saveDataDownToShader(ShaderProgram& prog) {
	prog.saveUniform("viewTransform",       ParameterType::PT_MAT4,     &viewTransform[0][0] );
	prog.saveUniform("enableOverrideColor", ParameterType::PT_BOOLEAN,  &enableOverrideColor );
	prog.saveUniform("overrideColor",       ParameterType::PT_VEC3,     &overrideColor[0]    );
	prog.saveUniform("ambientLight",        ParameterType::PT_VEC3,     &ambientLight[0]     );
	prog.saveUniform("diffuseLight",        ParameterType::PT_VEC3,     &diffuseLight[0]     );
	prog.saveUniform("diffusePos",          ParameterType::PT_VEC3,     &diffusePos[0]       );
	prog.saveUniform("diffuseInFrag",       ParameterType::PT_BOOLEAN,  &diffuseInFrag       );
	prog.saveUniform("specPower",           ParameterType::PT_FLOAT,    &specPower           );
	prog.saveUniform("specColor",           ParameterType::PT_VEC3,     &specColor[0]        );
	prog.saveUniform("camPos",              ParameterType::PT_VEC3,     &myCam.getPos()[0]   );
	prog.saveUniform("enableTexture",       ParameterType::PT_BOOLEAN,  &enableTexture       );
	prog.saveUniform("enableLighting",      ParameterType::PT_BOOLEAN,  &enableLighting      );
}

//returns floorID
uint loadModels(Neumont::ShapeData * models, uint * modelCount) {
	uint floorGeoID;
	int teaPotQuality = Random::randomInt(5,30);
	int randomQuality = 50;//Random::randomInt(5,15);
	models[(*modelCount)++] = NUShapeEditor::fixTeaPotNormals(NUShapeEditor::setModColor(Neumont::ShapeGenerator::makeTeapot(teaPotQuality,glm::mat4()),4));
	models[(*modelCount)++] = NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeTorus(randomQuality));
	models[(*modelCount)++] = NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeSphere(randomQuality));
	/* boring models
	models[(*modelCount)++] = NUShapeEditor::NUShapeEditorinitUVData(Neumont::ShapeGenerator::makeArrow());
	models[(*modelCount)++] = Neumont::ShapeGenerator::makeCube();
	models[(*modelCount)++] = BinaryToShapeLoader::loadFromFile("binaryModels/cube.bin");
	models[(*modelCount)++] = BinaryToShapeLoader::loadFromFile("binaryModels/plane.bin");
	//*/

	models[(*modelCount)++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../binaryModels/CartoonTree.bin"),10);
	models[(*modelCount)++] =					   BinaryToShapeLoader::loadFromFile("../binaryModels/GhoulOBJ.bin"   );
	models[(*modelCount)++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../binaryModels/gun.bin"        ),4);
	models[(*modelCount)++] =					   BinaryToShapeLoader::loadFromFile("../binaryModels/myChair.bin"    );
	models[(*modelCount)++] =					   BinaryToShapeLoader::loadFromFile("../binaryModels/phone.bin"      );
	models[(*modelCount)++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../binaryModels/TeddyBear.bin"  ),50);


	/*dont show up
	models[(*modelCount)++] = BinaryToShapeLoader::loadFromFile("binaryModels/Kitana.bin");
	models[(*modelCount)++] = BinaryToShapeLoader::loadFromFile("binaryModels/Fan.bin");
	models[(*modelCount)++] = BinaryToShapeLoader::loadFromFile("binaryModels/Skeleton.bin");
	//*/
	
	floorGeoID = *modelCount;//setting floor to plane;
	models[(*modelCount)++] = NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makePlane(10));
	return floorGeoID;
}

void MyWindow::generateRandomRenderable(uint count, GeometryInfo ** randomModels, uint randomModelCount, uint numOfTextures) {
	for (uint i = 0; i < count; i++) {
		int index = Random::randomInt(0,randomModelCount-1);
		Renderable * justAdded = myRender.addRenderable(randomModels[index],myRender.mainShader,Random::randomInt(0,numOfTextures-1));
		
		float x = Random::randomFloat(-range,range);
		float y = Random::randomFloat(0, range/2);
		float z = Random::randomFloat(-range,range);
		justAdded->addTranslate(glm::vec3(x,y,z));

		justAdded->saveRotationMat("model2RotationTransform");
		justAdded->saveWhereMat("model2WorldTransform");
		justAdded->saveTexture("myTexture");

		gameObjs[numOfGameObjs++] = justAdded;
	}
}
void MyWindow::sendDataToHardWare() {
	//setting up textures
	int numOfTextures = sendTextures(myRender);

	numOfGameObjs = 0;

	saveDataDownToShader(*myRender.mainShader);

	//NU shapes
	GeometryInfo * randomModels[20];
	uint randomModelCount = 0;
	Neumont::ShapeData models[20];
	uint modelCount = 0;
	uint floorGeoID = loadModels(&models[0],&modelCount);

	for(uint i=0;i<modelCount;i++) {
		GeometryInfo * justAdded = myRender.addGeometry(models[i],GL_TRIANGLES);
		//GeometryInfo * justAdded = myRender.addGeometry(models[i].verts,models[i].numVerts,models[i].indices,models[i].numIndices,GL_TRIANGLES);
		justAdded->NU_VertexStreamedPosition(0);
		justAdded->NU_VertexStreamedColor(1);
		justAdded->NU_VertexStreamedNormal(2);
		justAdded->NU_VertexStreamedUv(3);
		if(i==floorGeoID) {
			floor.whatGeo = justAdded;
		} else {
			randomModels[randomModelCount++] = justAdded;
		}
	} 

	generateRandomRenderable(numOfShapesToMake,&randomModels[0],randomModelCount,numOfTextures);
	
	int index = Random::randomInt(0,randomModelCount-1);
	lightSource.init(randomModels[index],myRender.mainShader,true,Random::randomInt(0,numOfTextures-1));
	lightSource.setScale(.75);
	lightSource.randomRange = 2;
	lightSource.saveRotationMat("model2RotationTransform");
	lightSource.saveWhereMat("model2WorldTransform");
	
	floor.init(floor.whatGeo,myRender.mainShader,true,Random::randomInt(0,numOfTextures-1));
	floor.setScale(range/2);
	floor.addTranslate(vec3(0,-5,0));
	floor.saveRotationMat("model2RotationTransform");
	floor.saveWhereMat("model2WorldTransform");
	floor.saveTexture("myTexture");
}

SingleKeyManager KEY_SPHERE           ('1'); // sphere
SingleKeyManager KEY_CUBE             ('2'); // cube
SingleKeyManager KEY_POINT            ('3'); // point
SingleKeyManager KEY_VEC              ('4'); // vector orgin to pos
SingleKeyManager KEY_LINE             ('5'); // line orgin to pos
SingleKeyManager KEY_INCREASE_LIFETIME(VK_UP);
SingleKeyManager KEY_DECREASE_LIFETIME(VK_DOWN);
SingleKeyManager KEY_INF_LIFETIME     ('0');
#include <limits>
uint currentLifeTime = 1;
bool lifetimeInf = true;
const uint lifetimeIncrementor = 1;

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/
	KEY_SPHERE.update(.1f);
	KEY_CUBE.update  (.1f);
	KEY_POINT.update (.1f);
	KEY_VEC.update   (.1f);
	KEY_LINE.update  (.1f);
	KEY_INCREASE_LIFETIME.update(.1f);
	KEY_DECREASE_LIFETIME.update(.1f);
	KEY_INF_LIFETIME.update     (.1f);

	float lifetime = (lifetimeInf)? std::numeric_limits<float>::infinity() : currentLifeTime;
	// HIPPO
	if(KEY_SPHERE.hasBeenClicked()) { myDebugShapes.addUnitSphere(glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_CUBE.hasBeenClicked())   { myDebugShapes.addUnitCube  (glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_POINT.hasBeenClicked())  { myDebugShapes.addPoint(myCam.getPos()+myCam.getViewDir(),lifetime); }
	if(KEY_VEC.hasBeenClicked())    { myDebugShapes.addUnitVector(glm::vec3(0,0,0),myCam.getPos()+myCam.getViewDir(),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_LINE.hasBeenClicked())   { myDebugShapes.addLine(glm::vec3(0,0,0),myCam.getPos()+myCam.getViewDir(),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_INCREASE_LIFETIME.hasBeenClicked())  { currentLifeTime += lifetimeIncrementor; }
	if(KEY_DECREASE_LIFETIME.hasBeenClicked())  { currentLifeTime -= lifetimeIncrementor; }
	if(KEY_INF_LIFETIME.hasBeenClicked())  { lifetimeInf = !lifetimeInf; }
	currentLifeTime = currentLifeTime < 1 ? 1 : currentLifeTime;
	
	
	if(frames%100==0) {
		//myDebugShapes.addPoint(myCam.getPos()+myCam.getViewDir());
		//myDebugShapes.addUnitSphere(glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1));
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	myDebugShapes.update(.1f);

	if(objectsMoving) {
		for (uint i = 0; i < myRender.getNumOfRenderables(); i++) {
			if(frames%1000==0) myRender.getRenderable(i)->randomACC();
				myRender.getRenderable(i)->rotate();
		}
	}
	if(frames%1000==0) lightSource.randomACC();
		lightSource.rotate();
	repaint();
	if(frames>10000)
		paintGL();
}
void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_LBUTTON)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}
void MyWindow::keyPressEvent(QKeyEvent* e) {
	if(e->key() == Qt::Key::Key_W) {
		myCam.moveForward();
	} else if(e->key() == Qt::Key::Key_S) {
		myCam.moveBackward();
	} else if(e->key() == Qt::Key::Key_A) {
		myCam.moveLeft();
	} else if(e->key() == Qt::Key::Key_D) {
		myCam.moveRight();
	} else if(e->key() == Qt::Key::Key_R) {
		myCam.moveUp();
	} else if(e->key() == Qt::Key::Key_F) {
		myCam.moveDown();
	}
}

void MyWindow::paintGL() {
	myRender.drawPrep(width(),height());
	
	const float aspectRatio = (float)width()/(float)height();
	viewTransform = glm::mat4();
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();

	//* comment to disable all draw calls

	//myDebugShapes.draw();
	

	bool passThrough = false;

	myRender.resetAllShaders_validPush();
	myRender.mainShader->useProgram();

	for (uint i = 0; i < numOfGameObjs; i++)
	{
		draw(*gameObjs[i],passThrough);
	}

	draw(floor,passThrough);

	passThrough = true;

	if(displayLightEntity) {
		lightSource.setTranslate(diffusePos);
		draw(lightSource,passThrough);
	}
	myDebugShapes.draw();
	//*/
}

void MyWindow::draw(Renderable& entity, bool passthrough) {
	if(entity.visible) {
		entity.howShader->useProgram();
		entity.howShader->passSavedUniforms_try();
		entity.howShader->passUniform("passThrough", ParameterType::PT_BOOLEAN, passthrough);
		entity.passUniformsDownDown();
		myRender.draw(*entity.whatGeo);
	}
}