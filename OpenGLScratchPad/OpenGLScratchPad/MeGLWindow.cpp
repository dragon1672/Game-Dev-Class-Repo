#include <GL\glew.h>
#include "MeGLWindow.h"
#include <Qt/qdebug.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
using glm::vec3;
using glm::mat4x4;

char * vertexShaderCode = "#version 400\r\n"
	""
	"in layout(location=0) vec2 pos;"
	""
	"out vec3 outColor;"
	""
	"uniform mat4x4 transformation;"
	"uniform vec3 dominatingColor;"
	""
	"void main() {"
		"gl_Position = transformation * vec4(pos.x,pos.y,1,1);"
		"outColor = dominatingColor;"
	"}"
	"";

char * fragShaderCode = "#version 400\r\n"
	""
	"in vec3 outColor;"//name must match
	"out vec3 finalColor;"
	""
	"void main() {"
	"	finalColor = outColor;"
	"}"
	"";

void MeGLWindow::initializeGL()
{
	glewInit();
	createTriange();
	initShaders();
	initPlayers();
	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}
///returns programID
int MeGLWindow::buildProgram(int numOfFiles, codeBlock * arrayOfBlocks, bool debug) {
	for(int i=0;i<numOfFiles;i++) {
		loadShader(arrayOfBlocks[i].code,arrayOfBlocks[i].id,debug);
	}
	
	GLuint programID = glCreateProgram();
	
	for(int i=0;i<numOfFiles;i++) {
		glAttachShader(programID,arrayOfBlocks[i].id);
	}

	glLinkProgram(programID);

	return programID;
}
void MeGLWindow::loadShader(char * code, GLuint id, bool debug) {
	const char * codeAdapt[1];
	codeAdapt[0] = code;
	glShaderSource(id,1,codeAdapt,0);

	glCompileShader(id);
	
	if(debug) {
		GLint compileStatus;
		glGetShaderiv(id,GL_COMPILE_STATUS, &compileStatus);
		if(compileStatus!= GL_TRUE) {
			GLint logLength;
			glGetShaderiv(id,GL_INFO_LOG_LENGTH,&logLength);
			char * buffer = new char[logLength];
			GLsizei someRandom;
			glGetShaderInfoLog(id,logLength,&someRandom,buffer);
			qDebug() << buffer;
			delete [] buffer;
		}
	}
}
void MeGLWindow::initShaders() {
	codeBlock blocks[2];
	blocks[0].id = glCreateShader(GL_VERTEX_SHADER);
	blocks[1].id = glCreateShader(GL_FRAGMENT_SHADER);
	blocks[0].code = vertexShaderCode;
	blocks[1].code = fragShaderCode;
	programID = buildProgram(2,blocks,true);
	glUseProgram(programID);
}
void MeGLWindow::initPlayers() {
	numOfPlayers=0;
	players[numOfPlayers++].initPlayer(vec3(1,0,0),vec3(-.3,0,0),'W','S','A','D');
	players[numOfPlayers++].initPlayer(vec3(0,1,0),vec3(+.3,0,0),VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT);
}

void MeGLWindow::createTriange() {
	GLfloat vertices[] = 
	{
		-0.5,+0.0, // 0
		+0.5,+0.0, // 1
		-0.5,-0.5, // 2
		+0.5,-0.5, // 3
		+.25,+0.5, // 4
		-.25,+0.5, // 5
		+.25,+0.0, // 6
		-.25,+0.0, // 7

		+.1,0, //8
		-.1,0, //9
		+0,1, //10
	};

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

	GLushort indices[] = {0,1,2, 1,2,3,	0,4,6, 1,5,7, 8,9,10};
	//GLushort indices[] = {8,9,10};
	GLuint indexBufferID;
	glGenBuffers(1,&indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

}
void MeGLWindow::myUpdate() {
	/*static int frames = 0;
	static const int frameUpdateRate = 1000;
	frames++;
	if(frames%frameUpdateRate==0)
		qDebug() << "frame: " << frames;
	//*/
	for(int i=0;i<numOfPlayers;i++) {
		players[i].update();
	}
	glClear(GL_COLOR_BUFFER_BIT);
	repaint();
}
void MeGLWindow::paintGL() {
	glViewport(0,0,width(),height());

	float aspectRatioFix = (float)height()/(float)width();
	mat4x4 aspectRatio = glm::scale(vec3(aspectRatioFix,1,1));

	mat4x4 transform;
	vec3 color;

	GLint transformationUniformLocation = glGetUniformLocation(programID,"transformation");
	GLint colorUniformLocation = glGetUniformLocation(programID,"dominatingColor");


	for(int i=0;i<numOfPlayers;i++) {
		transform = aspectRatio;
		transform *= players[i].getTransform();
		color = players[i].getColor();


		glUniform3fv(colorUniformLocation,1,&color[0]);
		glUniformMatrix4fv(transformationUniformLocation,1,false,&transform[0][0]);
		
		glDrawElements(GL_TRIANGLES,3 * 5,GL_UNSIGNED_SHORT,0);
	}
}