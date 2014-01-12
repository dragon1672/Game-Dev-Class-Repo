#include <GL\glew.h>
#include "MeGLWindow.h"
#include <Qt/qdebug.h>

char * vertexShaderCode = "#version 400\r\n"
	""
	"in layout(location=0) vec2 pos;"
	"in layout(location=1) vec3 col;"
	""
	"out vec3 outColor;"
	""
	""
	"void main() {"
	"	gl_Position = vec4(pos,1,1);"
	"	outColor = col;"
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
}

void MeGLWindow::loadShader(char * code, GLuint id) {
	const char * codeAdapt[1];
	codeAdapt[0] = code;
	glShaderSource(id,1,codeAdapt,0);

	glCompileShader(id);
	
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

void MeGLWindow::initShaders() {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	loadShader(vertexShaderCode,vertexShaderID);
	loadShader(fragShaderCode,fragShaderID);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragShaderID);

	glLinkProgram(programID);

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
void MeGLWindow::paintGL()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}