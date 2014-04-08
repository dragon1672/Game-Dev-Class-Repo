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


using glm::vec3;
using glm::mat4x4;

void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&myRender, &viewTransform[0][0]);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");
	myRender.mainShader->saveUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);

	sendDataToHardWare();

	setMouseTracking(true);
	
	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}

void MyWindow::init() {
	myCam.setPos(vec3(17,3.7f,-15),vec3(-50,-13,85));
}

void MyWindow::sendDataToHardWare() {
	//setting up textures
	numOfGameObjs = 0;

	Renderable * temp = myRender.addRenderable(myRender.addGeometry(Neumont::ShapeGenerator::makeSphere(20),GL_TRIANGLES),myRender.getShader(1));
	temp->whereMat = glm::translate(myCam.getPos()+3.0f*myCam.getViewDir());
	temp->saveWhereMat("model2WorldTransform");

	gameObjs[numOfGameObjs++] = temp;

	myDebugShapes.addPoint(myCam.getPos()+3.0f*myCam.getViewDir());
}

void MyWindow::myUpdate() {
	myDebugShapes.update(.1f);

	repaint();
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

	myRender.resetAllShaderPassDowns();
	//myRender.mainShader->useProgram();

	for (uint i = 0; i < numOfGameObjs; i++)
	{
		myRender.draw(*gameObjs[i]);
	}
	myDebugShapes.draw();
}