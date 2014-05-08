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

	setupGame();
}

void MyWindow::setupGame() {
	const int numOfPlayers = 2;
	glm::mat4 * TeamARenderables[numOfPlayers];
	glm::mat4 * TeamBRenderables[numOfPlayers];
	glm::mat4 * flagRenderableTransform;
	glm::mat4 * baseATransform;
	glm::mat4 * baseBTransform;

	//GeometryInfo * TeamAGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/TeddyBear.bin"),30), GL_TRIANGLES);
	GeometryInfo * TeamAGeo = myRender.addGeometry(BinaryToShapeLoader::loadFromFile("../gameData/Lego.bin"), GL_TRIANGLES);
	GeometryInfo * TeamBGeo = myRender.addGeometry(NUShapeEditor::setColor(glm::vec4(1,0,0,1),NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/TeddyBear.bin"),30)), GL_TRIANGLES);

	//uint TeamATexture = myRender.addTexture("\\..\\gameData\\TeamAText.png");
	uint TeamATexture = myRender.addTexture("\\..\\gameData\\LegoTexture.png");
	uint TeamBTexture = myRender.addTexture("\\..\\gameData\\TeamBText.png");

	for (int i = 0; i < numOfPlayers; i++)
	{
		Renderable * tempRenderable = myRender.addRenderable(TeamAGeo,myRender.mainShader,TeamATexture);
		gameObjs[numOfGameObjs++] = tempRenderable;
		tempRenderable->saveTexture("myTexture");
		tempRenderable->saveWhereMat("model2WorldTransform");
		TeamARenderables[i] = &tempRenderable->whereMat;

		//team B
		tempRenderable = myRender.addRenderable(TeamBGeo,myRender.mainShader,TeamBTexture);
		gameObjs[numOfGameObjs++] = tempRenderable;
		tempRenderable->saveTexture("myTexture");
		tempRenderable->saveWhereMat("model2WorldTransform");
		TeamBRenderables[i] = &tempRenderable->whereMat;

	}

	GeometryInfo * flagGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/Flag.bin"),1), GL_TRIANGLES);
	Renderable * flagRenderable = myRender.addRenderable(flagGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\FlagTexture.png"));
	gameObjs[numOfGameObjs++] = flagRenderable;
	flagRenderable->saveTexture("myTexture");
	flagRenderable->saveWhereMat("model2WorldTransform");
	flagRenderableTransform = &flagRenderable->whereMat;

	//Bases (A)
	GeometryInfo * baseGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/Base.bin"),1), GL_TRIANGLES);
	Renderable * baseRenderable = myRender.addRenderable(baseGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\BaseA.png"));
	gameObjs[numOfGameObjs++] = baseRenderable;
	baseRenderable->saveTexture("myTexture");
	baseRenderable->saveWhereMat("model2WorldTransform");
	baseATransform = &baseRenderable->whereMat;
	//Base B
	baseGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/Base.bin"),1), GL_TRIANGLES);
	baseRenderable = myRender.addRenderable(baseGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\BaseB.png"));
	gameObjs[numOfGameObjs++] = baseRenderable;
	baseRenderable->saveTexture("myTexture");
	baseRenderable->saveWhereMat("model2WorldTransform");
	baseBTransform = &baseRenderable->whereMat;


	myCTFGame.init(pather,myDebugShapes,numOfPlayers,TeamARenderables,TeamBRenderables,flagRenderableTransform);
	myCTFGame.registerBaseTransforms(baseATransform,baseBTransform);
	myCTFGame.randomSetBases(nodes,numOfNodes);
}
void MyWindow::init() {
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
	myTimer.start();
	showAllConnections = false;
	showAllConnections_lastState = true;
}
void MyWindow::addDebugMenu(DebugMenuManager * datMenu) {
	datMenu->toggleBool("Show All Connections",showAllConnections);
	datMenu->watchFloat("BaseA",myCTFGame.aBase.score);
	datMenu->watchFloat("BaseB",myCTFGame.bBase.score);
	datMenu->slideFloat("A1 Character Speed",myCTFGame.theATeam.members[0].speedMultiplyer,.1,10);
	datMenu->slideFloat("A2 Character Speed",myCTFGame.theATeam.members[1].speedMultiplyer,.1,10);
	datMenu->slideFloat("B1 Character Speed",myCTFGame.theBTeam.members[0].speedMultiplyer,.1,10);
	datMenu->slideFloat("B2 Character Speed",myCTFGame.theBTeam.members[1].speedMultiplyer,.1,10);
	datMenu->toggleBool("A1 togglePath",myCTFGame.theATeam.members[0].debugPath);
	datMenu->toggleBool("A2 togglePath",myCTFGame.theATeam.members[1].debugPath);
	datMenu->toggleBool("B1 togglePath",myCTFGame.theBTeam.members[0].debugPath);
	datMenu->toggleBool("B2 togglePath",myCTFGame.theBTeam.members[1].debugPath);
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
	myCTFGame.update(dt);

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