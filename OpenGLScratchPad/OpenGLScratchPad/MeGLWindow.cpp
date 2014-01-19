#include <GL\glew.h>
#include "MeGLWindow.h"
#include <Qt/qdebug.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
using glm::vec3;
using glm::mat4x4;

namespace ForReder {
	void * playerOffset = 0;
	void * hillOffset;
	int playerLength;
	int hillLength;
}

vec3 hillPos;
float hillScale = .1f;
int numOfFramesForHillJump = 60*5;

int maxPoints = 0;

void MeGLWindow::initializeGL()
{
	glewInit();

	glEnable(GL_DEPTH_TEST);

	createTriange();
	
	initShaders(); // NOW THIS IS PURDY!!
	initPlayers(); // not as purdy...but still nice

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}
void MeGLWindow::initPlayers() {
	numOfPlayers=0;
	players[numOfPlayers++].initPlayer(vec3(1,0,0),vec3(-.5,0,0),'W','S','A','D');
	players[numOfPlayers++].initPlayer(vec3(0,1,0),vec3(+.5,0,0),VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT);
	players[numOfPlayers++].initPlayer(vec3(0,0,1),vec3(0,.5,0),'Y','H','G','J');
}
void MeGLWindow::initShaders() {
	myShadyShaders.startup();
	myShadyShaders.addProgram("VertexShader.glsl",GL_VERTEX_SHADER);
	myShadyShaders.addProgram("FragShader.glsl",GL_FRAGMENT_SHADER);
	myShadyShaders.compileAndRun();
}
void MeGLWindow::createTriange() {
	GLfloat vertices[] = 
	{
		-0.5f, +0.0f, // 0
		+0.5f, +0.0f, // 1
		-0.5f, -0.5f, // 2
		+0.5f, -0.5f, // 3
		+.25f, +0.5f, // 4
		-.25f, +0.5f, // 5
		+.25f, +0.0f, // 6
		-.25f, +0.0f, // 7
		+0.1f, +0.0f, //8
		-0.1f, +0.0f, //9
		+0.0,  +1.0f, //10
		//the hill
		+0.0f,  +1.0f, //11
		+1.0f,  +.25f, //12
		-1.0f,  +.25f, //13
		+0.0f,  -1.0f, //14
		+1.0f,  -.25f, //15
		-1.0f,  -.25f, //16
		
		+.25f,  +.25f, //17
		+0.0f,  +.25f, //18
		+.25f,  +0.0f, //19
		-.25f,  -.25f, //20
	};

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);


	ForReder::playerLength = 5*3;
	ForReder::hillLength = 4*3;
	
	ForReder::hillOffset = (void *)ForReder::playerLength;

	GLushort indices[] = { //ship (5)
							0,1,2, 1,2,3,	0,4,6, 1,5,7, 8,9,10,
							//hill(4)
							11,12,13, 14,15,16, 17,18,19, 18,19,20,
							};
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
	maxPoints = 1;
	for(int i=0;i<numOfPlayers;i++) {
		players[i].update();
		maxPoints = (players[i].getPoints() > maxPoints)? players[i].getPoints() : maxPoints;
	}

	maxPoints++;

	for(int i=0;i<numOfPlayers;i++) {

		players[i].setDepth(-(float)players[i].getPoints()/maxPoints);

		for(int j=i+1;j<numOfPlayers;j++) {
			if(i != j && players[i].isColliding2D(players[j])) {
				qDebug() << "Collide between " << i << " and " << j;
			}
		}
		if(players[i].isColliding2D(hillPos,hillScale)) {
			qDebug() << "Collide between " << i << " and hill (" << players[i].getPoints() << ")";
			players[i].addPoint();
		}
	}

	if(frames%numOfFramesForHillJump==0) {
		float x = (rand()%2==0)? (float)rand()/RAND_MAX : -(float)rand()/RAND_MAX;
		float y = (rand()%2==0)? (float)rand()/RAND_MAX : -(float)rand()/RAND_MAX;
		
		qDebug() << "hillMove (" << x << "," << y << ")";
		hillPos = vec3(x,y,0);
	}
	repaint();
}
void MeGLWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	float aspectRatioFix = (float)height()/(float)width();
	mat4x4 aspectRatio = glm::scale(vec3(aspectRatioFix,1,1));

	mat4x4 transform;
	vec3 color;

	GLint transformationUniformLocation = glGetUniformLocation(myShadyShaders.getProgramID(),"transformation");
	GLint colorUniformLocation = glGetUniformLocation(myShadyShaders.getProgramID(),"dominatingColor");


	for(int i=0;i<numOfPlayers;i++) {
		transform = aspectRatio;
		transform *= players[i].getTransform();
		color = players[i].getColor();


		glUniform3fv(colorUniformLocation,1,&color[0]);
		glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);
		
		glDrawElements(GL_TRIANGLES,ForReder::playerLength,GL_UNSIGNED_SHORT,ForReder::playerOffset);
	}

	//* daw dat hil
	transform = aspectRatio;
	transform *= glm::translate(hillPos) * glm::scale(vec3(hillScale,hillScale,1));
	color = vec3(1,0,1);

	glUniform3fv(colorUniformLocation,1,&color[0]);
	glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);
		
	glDrawElements(GL_TRIANGLES,ForReder::hillLength,GL_UNSIGNED_SHORT,ForReder::hillOffset);
	//*/
}