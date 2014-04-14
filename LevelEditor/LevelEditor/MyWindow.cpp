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


SingleKeyManager KEY_ADD_NODE (VK_LBUTTON); // add node
SingleKeyManager DISPLAY_ALL  ('A'); // shows all connections

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

void MyWindow::init() {
	//setting defaults
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
}
void MyWindow::loadGeo(const char * binaryFilePath) {
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryFilePath);
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

void MyWindow::addNode(Ray& mouseRay) {
	vec3 planeNormal = vec3(0,1,0);

	float denominator = glm::dot(mouseRay.direction,planeNormal);
	if(denominator != 0) // 
	{
		vec3 planePointToRayOrigin = vec3(0,0,0) - mouseRay.origin;
		float neumorator = glm::dot(planePointToRayOrigin, planeNormal);
		float distance = neumorator/denominator;
		if(distance >= 0) {
			vec3 positionToPlace = mouseRay.origin + mouseRay.direction * distance;
			myDebugShapes.addUnitSphere(glm::translate(positionToPlace),vec4(0,0,1,1));
		}
	}
}

void MyWindow::nodeOperationClick() {
	Ray mouseRay = getMouseRay();
	addNode(mouseRay);
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/
	KEY_ADD_NODE.update(.1f);
	DISPLAY_ALL.update(.1f);
	GetAsyncKeyState(VK_LCONTROL);
	GetAsyncKeyState(VK_DELETE);
	GetAsyncKeyState(VK_SHIFT);


	if(KEY_ADD_NODE.hasBeenClicked()) { 
		if(GetAsyncKeyState(VK_SHIFT)!=0) {
			myNodeManager.connectClick(getMouseRay());
		} else {
			myNodeManager.addOrSelectClick(getMouseRay());
		}
	}
	if(GetAsyncKeyState(VK_DELETE)!=0) {
		myNodeManager.deleteNodeSelectedNode();
	}
	if(DISPLAY_ALL.hasBeenClicked() && GetAsyncKeyState(VK_LCONTROL)) {
		myNodeManager.activateAllConnections();
	}
	
	
	if(frames%100==0) {
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	myDebugShapes.update(.1f);

	repaint();
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