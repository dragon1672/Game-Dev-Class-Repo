#include <GL\glew.h>
#include "MyWindow.h"
#include <ShapeData.h>
#include <ShapeGenerator.h>

#include <glm/glm.hpp>

const char* vertexShader = "#version 2\r\n"
	""
	""
	""
	""
	"void main() {"
		""
		""
	"}";
const char* fragShader = "#version 2\r\n"
	""
	""
	""
	""
	"void main() {"
		""
		""
	"}";

GLint programID;
GLuint bufferID;

void MyWindow::initializeGL() {
	glewInit();

	//TODO compile shaders
}
void MyWindow::sendDataToHardware() {
	Neumont::ShapeData toAdd[5];
	toAdd[0] = Neumont::ShapeGenerator::makePlane(1);
	toAdd[1] = Neumont::ShapeGenerator::makeTorus(10);
	toAdd[2] = Neumont::ShapeGenerator::makeCube();
	toAdd[3] = Neumont::ShapeGenerator::makeArrow();

	
	int offset = 0;
	for(int i=0;i<4;i++) {
		myShapes[i].init(offset,toAdd[i]);
		offset = myShapes[i].getEndOffset();
	}

	glGenBuffers(1,&bufferID);
	glBindBuffer(GL_ARRAY_BUFFER,bufferID);
	glBufferData(GL_ARRAY_BUFFER,offset,nullptr,GL_STATIC_DRAW);

	for(int i=0;i<4;i++) {
		myShapes[i].sendToHardware(bufferID);
	}
}
void MyWindow::paint() {

}
