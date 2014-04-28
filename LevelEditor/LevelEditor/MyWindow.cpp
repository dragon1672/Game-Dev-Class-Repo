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

void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&viewTransform[0][0]);
	myNodeManager.init(&myDebugShapes);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");

	sendDataToHardWare();

	setMouseTracking(true);
	
	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
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
	showPath = true;
	myCharacter.speed = 1;
}

void MyWindow::addDebugMenu(DebugMenuManager * datMenu) {
	datMenu->toggleBool("Editor Mode",editorMode);
	datMenu->toggleBool("Put Camera on Character",camOnCharacter);
	datMenu->toggleBool("Show All Connections",showAllConnections);
	datMenu->toggleBool("Show Path",showPath);
	datMenu->slideFloat("Character Speed", myCharacter.speed,.1f,3);
}

void MyWindow::loadGeo(const char * binaryFilePath) {
	if(editorMode) {
		Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryFilePath);
		levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
	} else {
		qDebug() << "Geo Can only be loaded when in editor mode";
	}
}
void MyWindow::loadGeoFromBinary(char * binaryData) {
	if(editorMode) {
		Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromBinary(binaryData);
		levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
	} else {
		qDebug() << "Geo Can only be loaded when in editor mode";
	}
}

void MyWindow::prepForLevel() {
	if(editorMode) {
		myNodeManager.deleteAll();
	} else {
		qDebug() << "Geo Can only pre level when in editor mode";
	}
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
			//update path
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
	moveCam(e);
	GetAsyncKeyState(VK_SHIFT); // flush required to make it play nice
	GetAsyncKeyState(VK_LCONTROL); // flush required to make it play nice
	if(editorMode) {
		if(e->key() == Qt::Key_Delete) {
			if(GetAsyncKeyState(VK_SHIFT)!=0) {
				myNodeManager.deleteAll();
			} else {
				myNodeManager.deleteNodeSelectedNode();
			}
		} else if(e->key() == DISPLAY_ALL.getCheckedElement() && GetAsyncKeyState(VK_LCONTROL)) {
			myNodeManager.activateAllConnections();
		}
	} else {
		//don't think there should be anything
	}
}

void MyWindow::myUpdate() {
	float dt = gameTimer.interval();
	myDebugShapes.update(dt);

	if(editorMode_lastState != editorMode) {
		gNodes = myNodeManager.exportToGameNode(numOfGNodes);
		pather.init(gNodes,numOfGNodes);
		editorMode_lastState = editorMode;
	}


	if(!editorMode) {
		myCharacter.update(1);
		if(myCharacter.isComplete()) {
			GameNode * start = &gNodes[Random::randomInt(0,numOfGNodes)];
			for (int i = 0; i < numOfGNodes; i++)
			{
				if(gNodes[i].pos == myCharacter.path.currentDestination) {
					start = &gNodes[i];
					break;
				}
			}
			GameNode * end   = &gNodes[Random::randomInt(0,numOfGNodes)];
			AStar::Path temp = pather.getPath(start,end);
			temp.currentDestination = myCharacter.path.currentDestination;
			myCharacter.setPath(temp);
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