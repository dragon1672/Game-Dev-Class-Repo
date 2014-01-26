#include <GL\glew.h>
#include "MyWindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "MyRandom.h"

#include <ShapeGenerator.h>


using glm::vec3;
using glm::mat4x4;

Neumont::ShapeData singleShape;

void MyWindow::initializeGL() {
	glewInit();

	glEnable(GL_DEPTH_TEST);

	sendDataToHardWare();
	
	initShaders();

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
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

	for (int i = 0; i < 10; i++)
	{
		myGameObjs[numOfGameObjs].myShape = myShapes[i%numOfShapes];
		float range = 2;
		myGameObjs[numOfGameObjs].translation = glm::vec3(RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range));
		myGameObjs[numOfGameObjs].scale = .2f;
		numOfGameObjs++;
	}
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/

	for (int i = 0; i < numOfGameObjs; i++)
	{
		myGameObjs[i].update(frames);
	}

	repaint();
}

void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float aspectRatio = (float)width()/(float)height();

	GLint transformationUniformLocation = myShadyShader.getUniform("transformation");

	mat4x4 transform;
	transform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	transform *= glm::lookAt(vec3(1,-3,3),vec3(0,0,0),vec3(0,1,0));

	for (int i = 0; i < numOfGameObjs; i++)
	{
		DrawnObj& toDraw = myGameObjs[i].getShape();
		glm::mat4x4 finalTrans = transform;
		finalTrans *= myGameObjs[i].getTransform();

		glUniformMatrix4fv(transformationUniformLocation,1,false,&finalTrans[0][0]);

		toDraw.printPrep();
		glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
	}
}