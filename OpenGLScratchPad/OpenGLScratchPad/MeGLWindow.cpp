#include <GL\glew.h>
#include "MeGLWindow.h"
#include <Qt/qdebug.h>
#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

using glm::vec3;
using glm::mat4x4;

char * vertexShaderCode = "#version 400\r\n"
	""
	"in layout(location=0) vec2 pos;"
	"in layout(location=1) vec3 col;"
	""
	"out vec3 outColor;"
	""
	"uniform mat4x4 transformation;"
	""
	"void main() {"
		"gl_Position = transformation * vec4(pos.x,pos.y,1,1);"
		"outColor = col;"
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

GLuint programID;
//mat3x3 transformation;
vec3 translation;
const glm::vec4 acc(0,1,0,0);
float angle;
const float SPEED = .02f;
const float SCALE = .5f;
mat4x4 transformation;

void MeGLWindow::initializeGL()
{
	glewInit();
	createTriange();
	initShaders();
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

void MeGLWindow::createTriange() {
	GLfloat vertices[] = 
	{
		+0.0f, +0.8f,
		+1.0f, +0.0f, +0.0f,

		-0.8f, -0.8f,
		+0.0f, +1.0f, +0.0f,

		+0.8f, -0.8f,
		+0.0f, +0.0f, +1.0f,

	};

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));
}
void MeGLWindow::myUpdate() {
	/*static int frames = 0;
	static const int frameUpdateRate = 1000;
	frames++;
	if(frames%frameUpdateRate==0)
		qDebug() << "frame: " << frames;
	//*/
	const float angleAcc = 2;

	if(GetAsyncKeyState(VK_LEFT)) {
		angle += angleAcc;
	} else if(GetAsyncKeyState(VK_RIGHT)) {
		angle -= angleAcc;
	}
	if(GetAsyncKeyState(VK_UP)) {
		translation += SPEED * vec3(glm::rotate(angle,vec3(0,0,1)) * acc);
	} else if(GetAsyncKeyState(VK_DOWN)) {
		translation -= SPEED * vec3(glm::rotate(angle,vec3(0,0,1)) * acc);
	}
	
	
	if(GetAsyncKeyState(' ')) {
		qDebug() << "angle: " << angle << " trans: " << translation.x << "," << translation.y;
	}


	transformation = glm::translate(translation);
	transformation *= glm::rotate(angle,vec3(0,0,1));
	transformation *= glm::scale(vec3(SCALE,SCALE,1));



	GLint transformationUniformLocation = glGetUniformLocation(programID,"transformation");
	glUniformMatrix4fv(transformationUniformLocation,1,false,&transformation[0][0]);
	glClear(GL_COLOR_BUFFER_BIT);
	repaint();
}
void MeGLWindow::paintGL() {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}