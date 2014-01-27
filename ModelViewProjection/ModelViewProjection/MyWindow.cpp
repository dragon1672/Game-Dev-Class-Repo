#include <GL\glew.h>
#include "MyWindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "MyRandom.h"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt/qdebug.h>

#include <ShapeGenerator.h>


using glm::vec3;
using glm::mat4x4;

Neumont::ShapeData singleShape;

float orbitAngle;
float orbitAcc = .2f;

void MyWindow::initializeGL() {
	glewInit();

	glEnable(GL_DEPTH_TEST);

	sendDataToHardWare();
	
	initShaders();

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);

	myCam.setPos(vec3(17,-3.7f,-15),vec3(-50,-13,85));
}
void MyWindow::initShaders() {
	myShadyShader.startup();
	myShadyShader.addProgram("VertexShader.glsl",GL_VERTEX_SHADER);
	myShadyShader.addProgram("FragShader.glsl",GL_FRAGMENT_SHADER);
	myShadyShader.compileAndRun();
}

//returns the required size
int initShapeData(int &counter, DrawnObj * theArray) {
	Neumont::ShapeData models[5];
	
	models[0] = Neumont::ShapeGenerator::makeTeapot(10,glm::mat4());
	models[1] = Neumont::ShapeGenerator::makeTorus(10);
	models[2] = Neumont::ShapeGenerator::makeArrow();
	models[3] = Neumont::ShapeGenerator::makeCube();
	models[4] = Neumont::ShapeGenerator::makeSphere(10);
	models[0] = Neumont::ShapeGenerator::makeArrow();

	counter = 0;
	uint currentOffset = 0;

	for (int i = 0; i < sizeof(models)/sizeof(*models); i++)
	{
		theArray[counter].init(models[i], currentOffset);
		currentOffset = theArray[counter].endOffset();
		
		counter++;
	}
	return currentOffset;
}

void MyWindow::sendDataToHardWare() {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	numOfGameObjs = 0;
	GLuint requiredBufferSize = initShapeData(numOfShapes,myShapes);
	
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, requiredBufferSize, NULL, GL_STATIC_DRAW);

	for (int i = 0; i < numOfShapes; i++)
	{
		myShapes[i].sendToBuffer(bufferID);
		//myShapes[i].cleanUp();
	}
	for (int i = 0; i < numOfShapes; i++)
	{
		myShapes[i].setVertexAttrib(bufferID);
	}

	for (int i = 0; i < 100; i++)
	{
		int index = RANDOM::randomInt(0,numOfShapes);
		myGameObjs[numOfGameObjs].myShape = myShapes[index];
		float range = 2;
		//myGameObjs[numOfGameObjs].translation = glm::vec3(RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range));
		myGameObjs[numOfGameObjs].scale = 1;
		numOfGameObjs++;
	}
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/

	if(frames%100==0) {
		qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	for (int i = 0; i < numOfGameObjs; i++)
	{
		myGameObjs[i].update(frames);
	}

	orbitAngle += orbitAcc;

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

void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float aspectRatio = (float)width()/(float)height();

	mat4x4 transform;
	transform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	transform *= myCam.getWorld2View();

	draw(&myGameObjs[0],transform,1,2,5,glm::vec3(9,0,0),glm::vec3(0,1,0));

	transform *= glm::translate(vec3(0,-10,0));

	draw(&myGameObjs[0],transform,1,4,3,glm::vec3(9,0,0),glm::vec3(0,1,0));
	
	/*
	for (int i = 0; i < numOfGameObjs; i++)
	{
		DrawnObj& toDraw = myGameObjs[i].getShape();
		glm::mat4x4 finalTrans = transform;
		finalTrans *= myGameObjs[i].getTransform();

		glUniformMatrix4fv(myShadyShader.getUniform("transformation"),1,false,&finalTrans[0][0]);

		toDraw.printPrep();
		glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
	}
	//*/
}

void MyWindow::draw(GameObj * blockData, glm::mat4x4 lastTransform, float scale, int depth, int children, glm::vec3 orbitLength, glm::vec3 orbitAxis) {
	if(depth>=0) {
		float averageAngle = 360.0f/children;
		for (int i = 0; i < children; i++)
		{
			DrawnObj& toDraw = myGameObjs[i].getShape();
			//glm::vec4 previousTranslation = lastTransform * glm::vec4(0,0,0,0);
			//glm::mat4x4 transform = glm::translate(glm::vec3(previousTranslation));
			glm::mat4x4 transform = glm::rotate(orbitAngle + i*averageAngle,orbitAxis)
									* glm::translate(scale * orbitLength)
									* glm::scale(glm::vec3(scale,scale,scale));

			//transform = glm::translate(glm::vec3(previousTranslation)) * transform;
			transform = lastTransform * transform;

			glm::mat4x4 finalTrans = transform * blockData->getTransform();
			glUniformMatrix4fv(myShadyShader.getUniform("transformation"),1,false,&finalTrans[0][0]);

			toDraw.printPrep();
			glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());

			draw(blockData+1, transform,.6f * scale,depth-1,children, orbitLength, orbitAxis);
		}
	}
}