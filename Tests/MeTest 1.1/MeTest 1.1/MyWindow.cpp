#include <GL/glew.h>
#include "MyWindow.h"
#include <ShapeGenerator.h>
#include <fstream>
#include <Qt/qdebug.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <ctime>
#include <random>

void MyWindow::initializeGL() {
	glewInit();
	sendDataToHardware();
	initShaders();
	glEnable(GL_DEPTH_TEST);
	myCam.setPos(glm::vec3(0,-3.7f,-15),glm::vec3(-5,-13,85));
	setMouseTracking(true);
}

std::string file2str(const char * filePath) {
	std::ifstream file(filePath);
	return std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
}

void MyWindow::initShaders() {
	std::string VertexCode = file2str("Vertex");
	std::string FragCode = file2str("Frag");
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

	const char * adapt[1];
	adapt[0] = VertexCode.c_str();
	glShaderSource(vertexID,1,adapt,0);
	glCompileShader(vertexID);

	adapt[0] = FragCode.c_str();
	glShaderSource(fragID,1,adapt,0);
	glCompileShader(fragID);

	programID = glCreateProgram();

	glAttachShader(programID,fragID);
	glAttachShader(programID,vertexID);

	glLinkProgram(programID);
	glUseProgram(programID);
}

float randomFloat(float min, float max) {
	return ((float)rand()/RAND_MAX) * (max-min) + min;
}

void MyWindow::sendDataToHardware() {
	Neumont::ShapeData toAdd[5];
	//SingleBuffObj myShapes[5];

	srand((unsigned)time(0));

	toAdd[0] = Neumont::ShapeGenerator::makePlane(2);
	toAdd[1] = Neumont::ShapeGenerator::makeTorus(10);
	toAdd[2] = Neumont::ShapeGenerator::makeCube();
	toAdd[3] = Neumont::ShapeGenerator::makeArrow();

	uint generatedShapes = 4;
	
	uint offset = 0;
	for(uint i=0;i<generatedShapes;i++) {
		myShapes[i].init(toAdd[i],offset);
		offset = myShapes[i].endOffset();
	}

	glGenBuffers(1,&bufferID);
	glBindBuffer(GL_ARRAY_BUFFER,bufferID);
	glBufferData(GL_ARRAY_BUFFER,offset,nullptr,GL_STATIC_DRAW);

	for(uint i=0;i<generatedShapes;i++) {
		myShapes[i].sendToBuffer(bufferID);
	}
	numOfThings = 0;
	for (int i = 0; i < 500; i++)
	{
		float x = randomFloat(-100,100);
		float y = randomFloat(-100,100);
		float z = randomFloat(-100,100);
		float scale = randomFloat(.1f,10);
		myGameThings[numOfThings].init(myShapes[i%generatedShapes],glm::vec3(x,y,z),scale);
		numOfThings++;
	}

}

void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
		repaint();
	}
}
void MyWindow::keyPressEvent(QKeyEvent* e) {
	if(e->key() == Qt::Key::Key_W) {
		myCam.moveForward();
	} else if(e->key() == Qt::Key::Key_S) {
		myCam.moveBackward();
	} 
	if(e->key() == Qt::Key::Key_A) {
		myCam.moveLeft();
	} else if(e->key() == Qt::Key::Key_D) {
		myCam.moveRight();
	} 
	if(e->key() == Qt::Key::Key_R) {
		myCam.moveUp();
	} else if(e->key() == Qt::Key::Key_F) {
		myCam.moveDown();
	}
	repaint();
}


void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glm::mat4x4 transform;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	transform *= glm::perspective(60.0f,(float)width()/(float)height(),.1f,200.0f);
	transform *= myCam.getWorld2View();
	
	for (uint i = 0; i < numOfThings; i++)
	{
		glm::mat4x4 finalTrans = transform;
		finalTrans *= myGameThings[i].objectToWorld();


		SingleBuffObj toDraw = myGameThings[i].getMyStyle();
		//SingleBuffObj toDraw = myShapes[i];//myGameThings[i].getMyStyle();
		toDraw.printPrep();
		
		glUniformMatrix4fv(glGetUniformLocation(programID,"transformation"),1,false,&finalTrans[0][0]);

		glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
	}
}