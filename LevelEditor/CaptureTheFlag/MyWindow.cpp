#include <GL\glew.h>
#include "MyWindow.h"
#include "MyRandom.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/projection.hpp>


#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt/qdebug.h>

#include <ShapeGenerator.h>
#include "BinaryToShapeLoader.h"
#include "NUShapeEditor.h"

#include "SingleKeyManager.h"
#include "Ray.h"
#include "LevelSerializer.h"
#include "NUShapeEditor.h"
#include "NodeManager.h"


using glm::vec3;
using glm::vec4;
using glm::mat4x4;

const char * MyWindow::fileName = "myLevel.lvl";

#pragma region init

void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&viewTransform[0][0]);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");

	sendDataToHardWare();

	loadLevel(MyWindow::fileName);

	setMouseTracking(true);
	
	connect(&updateTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	updateTimer.start(0);

	GeometryInfo * tempGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/TeddyBear.bin"),30), GL_TRIANGLES);
	Renderable * tempRenderable = myRender.addRenderable(tempGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\ToonTeddyBear.png"));
	gameObjs[numOfGameObjs++] = tempRenderable;
	tempRenderable->saveTexture("myTexture");
	tempRenderable->saveWhereMat("model2WorldTransform");
	myCharacter.init(&tempRenderable->whereMat,&awesomeFlag,glm::vec3(0,0,5),pather,myDebugShapes);

	tempRenderable = myRender.addRenderable(tempGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\ToonTeddyBear.png"));
	gameObjs[numOfGameObjs++] = tempRenderable;
	tempRenderable->saveTexture("myTexture");
	tempRenderable->saveWhereMat("model2WorldTransform");

	awesomeFlag.init(&tempRenderable->whereMat);
}
void MyWindow::init() {
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
	myTimer.start();
	showAllConnections = false;
	showAllConnections_lastState = true;
}
void MyWindow::addDebugMenu(DebugMenuManager * datMenu) {
	datMenu->toggleBool("Show All Connections",showAllConnections);
}
#pragma endregion

#pragma region LoadingData
void MyWindow::loadLevel(const char * filePath) {
	myByte* levelBinary;
	LevelSerializer::readFile(filePath,levelBinary,nodes,numOfNodes);
	loadGeoFromBinary(levelBinary);
	delete levelBinary;
	pather.init(nodes,numOfNodes);
}
void MyWindow::loadGeoFromBinary(char * binaryData) {
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromBinary(binaryData);
	levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
}

void MyWindow::sendDataToHardWare() {
	mainTextureId = myRender.addTexture("\\..\\Textures\\mainTexture.png");

	numOfGameObjs = 0;

	myRender.mainShader -> saveUniform("viewTransform",       ParameterType::PT_MAT4,     &viewTransform[0][0] );
	levelRenderable = myRender.addRenderable(myRender.addGeometry(Neumont::ShapeGenerator::makePlane(30),GL_TRIANGLES),myRender.mainShader,mainTextureId);
	levelRenderable->saveWhereMat("model2WorldTransform");
	levelRenderable->saveTexture("myTexture");

	gameObjs[numOfGameObjs++] = levelRenderable;
}
#pragma endregion

#pragma region mouseAndKeys
Ray  MyWindow::getMouseRay() {
	Ray ret;
	QPoint p = mapFromGlobal(QCursor::pos());
	
	ret.init(glm::vec2(p.x(),p.y()),width(),height(),viewTransform,myCam);
	
	return ret;
}

void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_RBUTTON)!=0) {
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

#pragma endregion
#include "MyRandom.h"
void MyWindow::myUpdate() {
	float dt = myTimer.interval();
	myDebugShapes.update(dt);
	
	if(showAllConnections!=showAllConnections_lastState) {
		if(showAllConnections)
			pather.printAll(myDebugShapes,glm::vec4(0,0,1,1),glm::vec4(.5,.5,.5,1));
		else
			pather.clear();
		showAllConnections_lastState = showAllConnections;
		
	}
	awesomeFlag.update(dt);
	myCharacter.update(dt);

	repaint();
}


void MyWindow::paintGL() {
	myRender.drawPrep(width(),height());
	
	const float aspectRatio = (float)width()/(float)height();
	viewTransform = glm::mat4();
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();


	myRender.resetAllShaders_validPush();
	myRender.mainShader->useProgram();

	for (uint i = 0; i < numOfGameObjs; i++)
	{
		myRender.draw(*gameObjs[i]);
	}

	myDebugShapes.draw();
}