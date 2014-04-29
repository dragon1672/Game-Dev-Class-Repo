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


using glm::vec3;
using glm::vec4;
using glm::mat4x4;

//TODO: clear nodes on load

SingleKeyManager DISPLAY_ALL  ('A'); // shows all connections, used to store key not update

#pragma region GameNodeManagment

GameNode * closest(GameNode* gNodes, int numOfNodes, glm::vec3 currentPos) {
	float currentDist;
	GameNode * ret = nullptr;
	for (int i = 0; i < numOfNodes; i++)
	{
		float currentTestLength = glm::length(gNodes[i].pos - currentPos);
		if(ret == nullptr || currentTestLength <= currentDist) {
			currentDist = currentTestLength;
			ret = &gNodes[i];
		}
	}
	return ret;
}

GameNode * getNodeClicked(GameNode * leArray, int numOfNodes, Ray& ray, float radius=1) {
	for (int i = 0; i < numOfNodes; i++)
	{
		if(EditorNode::doesRayHit(ray,leArray[i].pos,radius)) {
			return &leArray[i];
		}
	}
	return nullptr;
}

#pragma endregion


void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&viewTransform[0][0]);
	myNodeManager.init(&myDebugShapes);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");

	sendDataToHardWare();

	setMouseTracking(true);
	
	connect(&updateTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	updateTimer.start(0);
	gameTimer.start();

	GeometryInfo * tempGeo = myRender.addGeometry(NUShapeEditor::scale(BinaryToShapeLoader::loadFromFile("../gameData/TeddyBear.bin"),30), GL_TRIANGLES);
	Renderable * tempRenderable = myRender.addRenderable(tempGeo,myRender.mainShader,myRender.addTexture("\\..\\gameData\\ToonTeddyBear.png"));
	gameObjs[numOfGameObjs++] = tempRenderable;
	tempRenderable->saveTexture("myTexture");
	tempRenderable->saveWhereMat("model2WorldTransform");
	myCharacter.init(&tempRenderable->whereMat);
}

void MyWindow::init() { //setting defaults
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
	gameTimer.start();
	editorMode = true;
	editorMode_lastState = false;
	camOnCharacter = false;
	showAllConnections = false;
	showAllConnections_lastState = true;
	showPath = true;
	showPath_lastState = false;
	myCharacter.speed = 1;
}

void MyWindow::addDebugMenu(DebugMenuManager * datMenu) {
	datMenu->toggleBool("Editor Mode",editorMode);
	datMenu->toggleBool("Put Camera on Character",camOnCharacter);
	datMenu->toggleBool("Show All Connections",showAllConnections);
	datMenu->toggleBool("Show Path",showPath);
	datMenu->slideFloat("Character Speed", myCharacter.speed,.1f,5);
}

void MyWindow::loadGeo(const char * binaryFilePath) {
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryFilePath);
	levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
}
void MyWindow::loadGeoFromBinary(char * binaryData) {
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromBinary(binaryData);
	levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
}

void MyWindow::prepForLevel() {
	myNodeManager.deleteAll();
}

void MyWindow::updatePath(GameNode * end) {
	GameNode * start = closest(gNodes,numOfGNodes,myCharacter.path.currentDestination);
	AStar::Path temp = pather.getPath(start,end);
	temp.currentDestination = myCharacter.path.currentDestination;
	myCharacter.setPath(temp, myDebugShapes);
	myCharacter.path.setVisability(showPath);
}
void MyWindow::updatePath(glm::vec3 newPos) {
	GameNode * end = closest(gNodes,numOfGNodes,newPos);
	updatePath(end);
}

bool MyWindow::inEditorState() { return editorMode; }

void MyWindow::sendDataToHardWare() {
	mainTextureId = myRender.addTexture("\\..\\Textures\\mainTexture.png");

	numOfGameObjs = 0;

	myRender.mainShader -> saveUniform("viewTransform",       ParameterType::PT_MAT4,     &viewTransform[0][0] );
	levelRenderable = myRender.addRenderable(myRender.addGeometry(Neumont::ShapeGenerator::makePlane(30),GL_TRIANGLES),myRender.mainShader,mainTextureId);
	levelRenderable->saveWhereMat("model2WorldTransform");
	levelRenderable->saveTexture("myTexture");

	gameObjs[numOfGameObjs++] = levelRenderable;
}

Ray  MyWindow::getMouseRay() {
	Ray ret;
	QPoint p = mapFromGlobal(QCursor::pos());
	
	ret.init(glm::vec2(p.x(),p.y()),width(),height(),viewTransform,myCam);
	
	return ret;
}

void MyWindow::mousePressEvent ( QMouseEvent * e ) {
	GetAsyncKeyState(VK_SHIFT); // flush required to make it play nice
	if(e->button() == Qt::LeftButton) {
		if(editorMode) {
			if(GetAsyncKeyState(VK_SHIFT)!=0) {
				myNodeManager.connectClick(getMouseRay());
			} else {
				myNodeManager.addOrSelectClick(getMouseRay());
			}
		} else {
			GameNode * selectedNode = getNodeClicked(gNodes,numOfGNodes,getMouseRay());
			if(selectedNode!=nullptr) {
				updatePath(selectedNode->pos);
			}
		}
	}
}

void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_RBUTTON)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}

void MyWindow::moveCam(QKeyEvent* e) {
	if(!camOnCharacter) {
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
}

void MyWindow::keyPressEvent(QKeyEvent* e) {
	GetAsyncKeyState(VK_SHIFT); // flush required to make it play nice
	GetAsyncKeyState(VK_LCONTROL); // flush required to make it play nice
	if(editorMode) {
		if(e->key() == Qt::Key_Delete) {
			if(GetAsyncKeyState(VK_SHIFT)!=0) {
				myNodeManager.deleteAll();
				return;
			} else {
				myNodeManager.deleteNodeSelectedNode();
				return;
			}
		} else if(e->key() == DISPLAY_ALL.getCheckedElement() && GetAsyncKeyState(VK_LCONTROL)) {
			myNodeManager.activateAllConnections();
			return;
		}
	} else {
		//don't think there should be anything
	}
	moveCam(e);
}

void MyWindow::myUpdate() {
	float dt = gameTimer.interval();
	myDebugShapes.update(dt);

	if(editorMode_lastState != editorMode) {
		gNodes = myNodeManager.exportToGameNode(numOfGNodes);
		pather.init(gNodes,numOfGNodes);
		//myNodeManager.setAllVisability(editorMode);
	}
	if(showAllConnections!=showAllConnections_lastState) {
		//if(showAllConnections) {
			//myNodeManager.activateAllConnections();
		//}
		myNodeManager.setAllVisability(showAllConnections);
	}
	if(showPath!=showPath_lastState) {
		myCharacter.path.setVisability(showPath);
	}
	
	editorMode_lastState = editorMode;
	showAllConnections_lastState = showAllConnections;
	showPath_lastState = showPath;

	if(!editorMode) {
		myCharacter.update(1);
		if(myCharacter.isComplete()) {
			int endID = Random::randomInt(0,numOfGNodes);
			GameNode * end   = &gNodes[endID];
			updatePath(end);
			
		}
	}
	repaint();
}


void MyWindow::paintGL() {
	myRender.drawPrep(width(),height());
	
	const float aspectRatio = (float)width()/(float)height();
	viewTransform = glm::mat4();
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	if(camOnCharacter) {
		viewTransform *= myCharacter.getWorld2View();
	} else {
		viewTransform *= myCam.getWorld2View();
	}


	myRender.resetAllShaders_validPush();
	myRender.mainShader->useProgram();

	for (uint i = 0; i < numOfGameObjs; i++)
	{
		myRender.draw(*gameObjs[i]);
	}

	myDebugShapes.draw();
}