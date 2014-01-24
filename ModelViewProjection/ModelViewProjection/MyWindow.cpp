#include <GL\glew.h>
#include "MyWindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

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
void MyWindow::sendDataToHardWare() {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);

	singleShape = Neumont::ShapeGenerator::makeArrow();
	
	glBufferData(GL_ARRAY_BUFFER, singleShape.vertexBufferSize(), singleShape.verts, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)Neumont::Vertex::POSITION_OFFSET);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)Neumont::Vertex::COLOR_OFFSET);
	
	//points
	GLuint indexBufferID;
	glGenBuffers(1,&indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,singleShape.indexBufferSize(),singleShape.indices,GL_STATIC_DRAW);

}

void MyWindow::myUpdate() {
	//*
	static int frames = 0;
	frames++;
	//*/

	repaint();
}

void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float aspectRatio = (float)width()/(float)height();

	GLint transformationUniformLocation = glGetUniformLocation(myShadyShader.getProgramID(),"transformation");

	mat4x4 transform;
	transform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	transform *= glm::lookAt(vec3(1,-3,3),vec3(0,0,0),vec3(0,1,0));

	glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);
	glDrawElements(GL_TRIANGLES,singleShape.numIndices,GL_UNSIGNED_SHORT,0);
}