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
#include "DebugShapeManager.h"


using glm::vec3;
using glm::mat4x4;

Neumont::ShapeData singleShape;

float orbitAngle;
float orbitAcc = .2f;

void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&myRender);

		myRender.mainShader->buildBasicProgram("VertexShader.glsl","FragShader.glsl");

	sendDataToHardWare();
	
	//myRender.mainShader->buildBasicProgram("VertexShader.glsl","FragShader.glsl");

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}

void MyWindow::init() {
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
}

int sendTextures(Renderer& myRender) {
	int numOfTextures;
	numOfTextures = myRender.addTexture("\\Textures\\black eyes.png");
	numOfTextures = myRender.addTexture("\\Textures\\blueLInes.png");
	numOfTextures = myRender.addTexture("\\Textures\\bsod.png");
	numOfTextures = myRender.addTexture("\\Textures\\color bands.png");
	numOfTextures = myRender.addTexture("\\Textures\\ComfyChair_Diffuse2.png");
	numOfTextures = myRender.addTexture("\\Textures\\face hands.png");
	numOfTextures = myRender.addTexture("\\Textures\\green matrix.png");
	numOfTextures = myRender.addTexture("\\Textures\\jamie Avatar.png");
	numOfTextures = myRender.addTexture("\\Textures\\obama bill.png");
	numOfTextures = myRender.addTexture("\\Textures\\Rust.png");
	numOfTextures = myRender.addTexture("\\Textures\\slaceRocks.png");
	numOfTextures = myRender.addTexture("\\Textures\\Smile.png");
	numOfTextures = myRender.addTexture("\\Textures\\ToonTeddyBear.png");
	numOfTextures = myRender.addTexture("\\Textures\\wood2.png");
	return numOfTextures;
}

void MyWindow::sendDataToHardWare() {
	//setting up textures
	int numOfTextures = sendTextures(myRender);

	numOfGameObjs = 0;

	uint floorGeoID;

	//NU shapes
	GeometryInfo * randomModels[20];
	uint randomModelCount = 0;
	Neumont::ShapeData models[20];
	uint modelCount = 0;
	int teaPotQuality = RANDOM::randomInt(5,30);
	int randomQuality = 50;//RANDOM::randomInt(5,15);
	models[modelCount++] = NUShapeEditor::fixTeaPotNormals(NUShapeEditor::setModColor(Neumont::ShapeGenerator::makeTeapot(teaPotQuality,glm::mat4()),4));
	models[modelCount++] = NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeTorus(randomQuality));
	//models[modelCount++] = NUShapeEditor::NUShapeEditorinitUVData(Neumont::ShapeGenerator::makeArrow());
	models[modelCount++] = NUShapeEditor::initUVData(Neumont::ShapeGenerator::makeSphere(randomQuality));
	//models[modelCount++] = Neumont::ShapeGenerator::makeCube();
	//models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/cube.bin");
	//models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/plane.bin");
	
	models[modelCount++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("binaryModels/CartoonTree.bin"),10);
	models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/GhoulOBJ.bin");
	models[modelCount++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("binaryModels/gun.bin"),4);
	models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/myChair.bin");
	models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/phone.bin");
	models[modelCount++] = NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("binaryModels/TeddyBear.bin"),50);


	//dont show up
	//models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/Kitana.bin");
	//models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/Fan.bin");
	//models[modelCount++] = BinaryToShapeLoader::loadFromFile("binaryModels/Skeleton.bin");
	
	floorGeoID = modelCount;//setting floor to plane;
	models[modelCount++] = NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makePlane(10));

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
	

	for (int i = 0; i < 50; i++) {
		int index = RANDOM::randomInt(0,randomModelCount-1);
		Renderable * justAdded = myRender.addRenderable(randomModels[index],myRender.mainShader,RANDOM::randomInt(0,numOfTextures-1));
		
		
		float x = RANDOM::randomFloat(-range,range);
		float y = RANDOM::randomFloat(0, range/2);
		float z = RANDOM::randomFloat(-range,range);
		justAdded->addTranslate(glm::vec3(x,y,z));

		justAdded->saveRotationMat("model2RotationTransform");
		justAdded->saveWhereMat("model2WorldTransform");
		justAdded->saveTexture("myTexture");

		gameObjs[numOfGameObjs++] = justAdded;
	}
	int index = RANDOM::randomInt(0,randomModelCount-1);
	lightSource.init(randomModels[index],myRender.mainShader,true,RANDOM::randomInt(0,numOfTextures-1));
	lightSource.setScale(.75);
	lightSource.randomRange = 2;
	lightSource.saveRotationMat("model2RotationTransform");
	lightSource.saveWhereMat("model2WorldTransform");
	
	floor.init(floor.whatGeo,myRender.mainShader,true,RANDOM::randomInt(0,numOfTextures-1));
	floor.setScale(10);
	floor.addTranslate(vec3(0,-5,0));
	floor.saveRotationMat("model2RotationTransform");
	floor.saveWhereMat("model2WorldTransform");
	floor.saveTexture("myTexture");
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/

	myDebugShapes.update(.1f);

	if(frames%100==0) {
		myDebugShapes.addPoint(myCam.getPos()+myCam.getViewDir());
		myDebugShapes.addUnitSphere(glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1));
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	if(objectsMoving) {
		for (uint i = 0; i < myRender.getNumOfRenderables(); i++) {
			if(frames%1000==0) myRender.getRenderable(i)->randomACC();
				myRender.getRenderable(i)->rotate();
		}
	}
	if(frames%1000==0) lightSource.randomACC();
		lightSource.rotate();
	repaint();
}
void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	glm::vec2 newPos(e->x(),e->y());
	myCam.updateMousePos(newPos);
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

void MyWindow::passDataDownToShader(ShaderProgram& prog, bool passthrough) {
	const float aspectRatio = (float)width()/(float)height();

	mat4x4 viewTransform;
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();

	prog.passUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);
	
	prog.passUniform("enableOverrideColor",ParameterType::PT_BOOLEAN,  enableOverrideColor);
	prog.passUniform("overrideColor",      ParameterType::PT_VEC3, &overrideColor[0]   );
	prog.passUniform("ambientLight",       ParameterType::PT_VEC3, &ambientLight[0]    );
	prog.passUniform("diffuseLight",       ParameterType::PT_VEC3, &diffuseLight[0]    );
	prog.passUniform("diffusePos",         ParameterType::PT_VEC3, &diffusePos[0]      );
	prog.passUniform("diffuseInFrag",      ParameterType::PT_BOOLEAN,  diffuseInFrag      );
	
	prog.passUniform("specPower", ParameterType::PT_FLOAT,&specPower);
	prog.passUniform("specColor", ParameterType::PT_VEC3, &specColor[0]);
	prog.passUniform("camPos",    ParameterType::PT_VEC3, &myCam.getPos()[0]);
	
	prog.passUniform("enableTexture",  ParameterType::PT_BOOLEAN, enableTexture);
	prog.passUniform("enableLighting", ParameterType::PT_BOOLEAN, enableLighting);
	prog.passUniform("passThrough", ParameterType::PT_BOOLEAN, passthrough);

}

void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bool passThrough = false;

	myRender.mainShader->useProgram();
	passDataDownToShader(*myRender.mainShader,passThrough);
	
	for (uint i = 0; i < numOfGameObjs; i++)
	{
		draw(*gameObjs[i],passThrough);
	}

	draw(floor,passThrough);

	passThrough = true;

	myRender.mainShader->passUniform("passThrough", ParameterType::PT_BOOLEAN, passThrough);

	if(displayLightEntity) {
		lightSource.setTranslate(diffusePos);
		draw(lightSource,passThrough);
	}
	const float aspectRatio = (float)width()/(float)height();
	mat4x4 viewTransform;
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();
	myDebugShapes.draw(viewTransform);
}

void MyWindow::draw(Renderable& entity, bool passthrough) {
	if(entity.visible) {
		if(!entity.howShader->isCurrentProgram()) {
			passDataDownToShader(*entity.howShader,passthrough);
		}
		entity.passUniformsDownDown();
		myRender.draw(*entity.whatGeo);
	}
}