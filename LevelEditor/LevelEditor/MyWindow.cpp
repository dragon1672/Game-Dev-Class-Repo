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
}

void MyWindow::init() { //setting defaults
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
}
void MyWindow::loadGeo(const char * binaryFilePath) {
	myNodeManager.deleteAll();
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryFilePath);
	levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
}
void MyWindow::loadGeo(uint offset, char * binaryData) {
	myNodeManager.deleteAll();
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryData, offset);
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

Ray  MyWindow::getMouseRay() {
	Ray ret;
	QPoint p = mapFromGlobal(QCursor::pos());
	
	ret.init(glm::vec2(p.x(),p.y()),width(),height(),viewTransform,myCam);
	
	return ret;
}

void MyWindow::mousePressEvent ( QMouseEvent * e ) {
	GetAsyncKeyState(VK_SHIFT); // flush required to make it play nice
	if(e->button() == Qt::LeftButton) {
		if(GetAsyncKeyState(VK_SHIFT)!=0) {
			myNodeManager.connectClick(getMouseRay());
		} else {
			myNodeManager.addOrSelectClick(getMouseRay());
		}
	} else if(e->button() == Qt::Key_Delete) {
		qDebug() << "delete on mouse press event";
	}
}

void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_RBUTTON)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}

void MyWindow::moveCam(QKeyEvent* e) {
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

void MyWindow::keyPressEvent(QKeyEvent* e) {
	moveCam(e);
	GetAsyncKeyState(VK_SHIFT); // flush required to make it play nice
	GetAsyncKeyState(VK_LCONTROL); // flush required to make it play nice
	if(e->key() == Qt::Key_Delete) {
		if(GetAsyncKeyState(VK_SHIFT)!=0) {
			myNodeManager.deleteAll();
		} else {
			myNodeManager.deleteNodeSelectedNode();
		}
	} else if(e->key() == DISPLAY_ALL.getCheckedElement() && GetAsyncKeyState(VK_LCONTROL)) {
		myNodeManager.activateAllConnections();
	}
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/
	
	if(frames%100==0) {
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	myDebugShapes.update(.1f);

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