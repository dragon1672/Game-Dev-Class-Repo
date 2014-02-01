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
	uniforms.clear();
	qDebug() << "Creating Shader Program ID: " << programID;
}
void ShaderProgram::shutdown() {
	// ?
}
bool ShaderProgram::addProgram(const char * filePath, unsigned short shaderType) {
	bool isValid = validFile(filePath);
	qDebug() << "\nAttempting to load file: " << filePath;
	if(isValid) {
		blocks[numOfFiles].code = file2str(filePath);
		blocks[numOfFiles].id = glCreateShader(shaderType);
		qDebug() << "File Load Successful ID: " << blocks[numOfFiles].id;

		isValid = complileShader(blocks[numOfFiles].code.c_str(),blocks[numOfFiles].id,true);
		if(isValid) {
			glAttachShader(programID,blocks[numOfFiles].id);
			qDebug() << "File(" << blocks[numOfFiles].id << ") Complile Successful ProgramID: " << programID << "\n";
			numOfFiles++;
		} else {
			qDebug() << "File(" << blocks[numOfFiles].id << ") Failed to Complile - NOT ADDED TO PROGRAM\n";
		}
	}
	return isValid;
}

int ShaderProgram::generateUniform(char* title) {
	return glGetUniformLocation(getProgramID(),title);
}
int ShaderProgram::getUniform(char* title) {
	int ret = -1;

	if(uniforms.count(title)==0) ret = generateUniform(title);
	else ret = uniforms[title];
	
	return ret;
}

bool ShaderProgram::complileShader(const char * code, GLuint id, bool debug) {
	bool valid = true;
	const char * codeAdapt[1];
	codeAdapt[0] = code;
	glShaderSource(id,1,codeAdapt,0);
	
	//qDebug() << "Compiling Shader " << id;
	glCompileShader(id);
	

	if(debug) {
		GLint compileStatus;
		glGetShaderiv(id,GL_COMPILE_STATUS, &compileStatus);
		if(compileStatus != GL_TRUE) {
			GLint logLength;
			glGetShaderiv(id,GL_INFO_LOG_LENGTH,&logLength);
			char * buffer = new char[logLength];
			GLsizei someRandom;
			glGetShaderInfoLog(id,logLength,&someRandom,buffer);
			qDebug() << buffer;
			delete [] buffer;

			valid = false;
		}
	}
	return valid;
}

void ShaderProgram::compileAndLink() {
	for(int i=0;i<numOfFiles;i++) {
		//complileShader(blocks[i].code.c_str(),blocks[i].id,true);
		//glAttachShader(programID,blocks[i].id);
	}
	qDebug() << "Linking Program ID: " << programID;
	glLinkProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
	return programID;
}
void ShaderProgram::useProgram() {
	qDebug() << "Regestering Shader Program " << programID << " into pipeline\n\n";
	glUseProgram(programID);
}

GLuint ShaderProgram::compileAndRun() {
	compileAndLink();
	useProgram();
	return programID;
}