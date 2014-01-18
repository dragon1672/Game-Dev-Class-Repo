#include <GL\glew.h>
#include "ShaderProgram.h"
#include <fstream>
#include <Qt/qdebug.h>

 std::string ShaderProgram::file2str(const char * filePath) {
	std::ifstream file(filePath);
	return std::string(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
}
bool ShaderProgram::validFile(const char * filePath) {
	std::ifstream file(filePath);
	bool valid = file.good();
	file.close();
	return valid;
}

void ShaderProgram::startup() {
	programID = glCreateProgram();
	numOfFiles = 0;
}
void ShaderProgram::shutdown() {
	// ?
}
bool ShaderProgram::addProgram(const char * filePath, unsigned short shaderType) {
	bool isValid = validFile(filePath);
	if(isValid) {
		blocks[numOfFiles].code = file2str(filePath);
		blocks[numOfFiles].id = glCreateShader(shaderType);
		numOfFiles++;
	}
	return isValid;
}

void ShaderProgram::complileShader(const char * code, GLuint id, bool debug) {
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

void ShaderProgram::compileAndLink() {
	for(int i=0;i<numOfFiles;i++) {
		complileShader(blocks[i].code.c_str(),blocks[i].id,true);
		glAttachShader(programID,blocks[i].id);
	}
	glLinkProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
	return programID;
}
void ShaderProgram::useProgram() {
	glUseProgram(programID);
}

GLuint ShaderProgram::compileAndRun() {
	compileAndLink();
	useProgram();
	return programID;
}