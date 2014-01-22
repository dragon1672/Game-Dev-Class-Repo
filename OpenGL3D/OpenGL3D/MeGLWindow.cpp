#include <GL\glew.h>
#include "MeGLWindow.h"
#include <Qt/qdebug.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "Randomness.h"
#include <cmath>

using glm::vec3;
using glm::mat4x4;

namespace ForReder {
	int vertsToDraw;
	vec3 worldTrans(0,0,-4);
	int depth = 2;
	int children = 3;
	float scale = .1;
}

void MeGLWindow::initializeGL()
{
	glewInit();

	glEnable(GL_DEPTH_TEST);

	createTriange();
	
	initShaders(); // NOW THIS IS PURDY!!

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);

	numOfCubes = pow(ForReder::children,ForReder::depth) + 1;
	cubeData = new CubeSolarSystem[numOfCubes];
	for (int i = 0; i < numOfCubes; i++)
	{
		cubeData[i] = CubeSolarSystem();
	}

}
void MeGLWindow::initShaders() {
	myShadyShaders.startup();
	myShadyShaders.addProgram("VertexShader.glsl",GL_VERTEX_SHADER);
	myShadyShaders.addProgram("FragShader.glsl",GL_FRAGMENT_SHADER);
	myShadyShaders.compileAndRun();
}
void MeGLWindow::createTriange() {

	vec3 verts[] = {
			vec3(-1.0f, +1.0f, +1.0f), // 0
			vec3(+1.0f, +0.0f, +0.0f), // Color
			vec3(+1.0f, +1.0f, +1.0f), // 1
			vec3(+0.0f, +1.0f, +0.0f), // Color
			vec3(+1.0f, +1.0f, -1.0f), // 2
			vec3(+0.0f, +0.0f, +1.0f), // Color
			vec3(-1.0f, +1.0f, -1.0f), // 3
			vec3(+1.0f, +1.0f, +1.0f), // Color
			
			vec3(-1.0f, +1.0f, -1.0f), // 4
			vec3(+1.0f, +0.0f, +1.0f), // Color
			vec3(+1.0f, +1.0f, -1.0f), // 5
			vec3(+0.0f, +0.5f, +0.2f), // Color
			vec3(+1.0f, -1.0f, -1.0f), // 6
			vec3(+0.8f, +0.6f, +0.4f), // Color
			vec3(-1.0f, -1.0f, -1.0f), // 7
			vec3(+0.3f, +1.0f, +0.5f), // Color
			
			vec3(+1.0f, +1.0f, -1.0f), // 8
			vec3(+0.2f, +0.5f, +0.2f), // Color
			vec3(+1.0f, +1.0f, +1.0f), // 9
			vec3(+0.9f, +0.3f, +0.7f), // Color
			vec3(+1.0f, -1.0f, +1.0f), // 10
			vec3(+0.3f, +0.7f, +0.5f), // Color
			vec3(+1.0f, -1.0f, -1.0f), // 11
			vec3(+0.5f, +0.7f, +0.5f), // Color
			
			vec3(-1.0f, +1.0f, +1.0f), // 12
			vec3(+0.7f, +0.8f, +0.2f), // Color
			vec3(-1.0f, +1.0f, -1.0f), // 13
			vec3(+0.5f, +0.7f, +0.3f), // Color
			vec3(-1.0f, -1.0f, -1.0f), // 14
			vec3(+0.4f, +0.7f, +0.7f), // Color
			vec3(-1.0f, -1.0f, +1.0f), // 15
			vec3(+0.2f, +0.5f, +1.0f), // Color
			
			vec3(+1.0f, +1.0f, +1.0f), // 16
			vec3(+0.6f, +1.0f, +0.7f), // Color
			vec3(-1.0f, +1.0f, +1.0f), // 17
			vec3(+0.6f, +0.4f, +0.8f), // Color
			vec3(-1.0f, -1.0f, +1.0f), // 18
			vec3(+0.2f, +0.8f, +0.7f), // Color
			vec3(+1.0f, -1.0f, +1.0f), // 19
			vec3(+0.2f, +0.7f, +1.0f), // Color
			
			vec3(+1.0f, -1.0f, -1.0f), // 20
			vec3(+0.8f, +0.3f, +0.7f), // Color
			vec3(-1.0f, -1.0f, -1.0f), // 21
			vec3(+0.8f, +0.9f, +0.5f), // Color
			vec3(-1.0f, -1.0f, +1.0f), // 22
			vec3(+0.5f, +0.8f, +0.5f), // Color
			vec3(+1.0f, -1.0f, +1.0f), // 23
			vec3(+0.9f, +1.0f, +0.2f), // Color
		};

	unsigned short indices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right 
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};


	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	const int sizeOfPoints = 3;
	const int sizeOfColor  = 3;

	//verts
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeOfPoints, GL_FLOAT, GL_FALSE, (2) * sizeof(vec3), 0);

	//colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeOfColor, GL_FLOAT, GL_FALSE, (2) * sizeof(vec3), (void*)(sizeof(vec3)));
	
	//points
	ForReder::vertsToDraw = sizeof(indices) / sizeof(*indices);
	GLuint indexBufferID;
	glGenBuffers(1,&indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

}

void MeGLWindow::myUpdate() {
	//*
	static int frames = 0;
	frames++;
	//*/
	
	for (int i = 0; i < numOfCubes; i++)
	{
		cubeData[i].update(frames);
	}

	repaint();
}
void MeGLWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float aspectRatio = (float)width()/(float)height();

	mat4x4 transform;

	GLint transformationUniformLocation = glGetUniformLocation(myShadyShaders.getProgramID(),"transformation");

	transform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	transform *= glm::translate(ForReder::worldTrans);
	transform *= glm::scale(vec3(ForReder::scale,ForReder::scale,ForReder::scale));

	//draw all the other ones
	for (int i = 1; i < numOfCubes; i++)
	{
		cubeData[i].draw(transformationUniformLocation,transform,ForReder::vertsToDraw,0,1,ForReder::depth,ForReder::children);
	}

	//draw the center cube
	transform *= cubeData[0].getTransform();
	glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);
	glDrawElements(GL_TRIANGLES,ForReder::vertsToDraw,GL_UNSIGNED_SHORT,0);

}