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
	GLuint requiredBufferSize = 0;

	Neumont::ShapeData models[5];
	
	models[0] = Neumont::ShapeGenerator::makeCube();
	models[1] = Neumont::ShapeGenerator::makeSphere(10);
	models[2] = Neumont::ShapeGenerator::makeTorus(10);
	models[3] = Neumont::ShapeGenerator::makeArrow();
	models[4] = Neumont::ShapeGenerator::makeTeapot(10,glm::mat4());

	counter = 0;
	uint currentOffset = 0;

	for (int i = 0; i < sizeof(models)/sizeof(*models); i++)
	{
		theArray[counter].init(models[i], currentOffset);
		requiredBufferSize += theArray[counter].totalBufferSize();
		currentOffset += theArray[counter].endOffset();
		
		counter++;
	}
	return requiredBufferSize;
}

void MyWindow::sendDataToHardWare() {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);

	GLuint requiredBufferSize = initShapeData(numOfShapes,myShapes);

	glBufferData(GL_ARRAY_BUFFER, requiredBufferSize, 0, GL_STATIC_DRAW);

	for (int i = 0; i < numOfShapes; i++)
	{
		myShapes[i].sendToBuffer(bufferID);
		//myShapes[i].cleanUp();
	}

	for (int i = 0; i < 10; i++)
	{
		myGameObjs[i].myShape = myShapes[i%numOfShapes];
		float range = .5;
		myGameObjs[i].translation = glm::vec3(RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range),RANDOM::randomFloat(-range,range));
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
		glm::mat4x4 finalTrans = transform;
		transform * myGameObjs[i].getTransform();

		glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);

		myGameObjs[i].getShape().printPrep();
		glDrawElements(GL_TRIANGLES,myGameObjs[i].getShape().numIndices,GL_UNSIGNED_SHORT,(void*)myGameObjs[i].getShape().indicesOffset());
	}
}