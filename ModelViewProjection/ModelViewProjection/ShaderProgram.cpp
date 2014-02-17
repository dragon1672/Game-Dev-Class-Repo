#include <GL\glew.h>
#include "ShaderProgram.h"
#include <fstream>
#include <Qt/qdebug.h>
#include <Qt/qcoreapplication.h>
#include <Qt/qimage.h>

GLuint ShaderProgram::currentProgram;

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
	qDebug() << "Creating Shader Program ID: " << programID;
}
void ShaderProgram::shutdown() {
	// ?
}
void ShaderProgram::buildBasicProgram(const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	startup();
	addProgram(vertexShaderFilePath,GL_VERTEX_SHADER);
	addProgram(fragmentShaderFilePath,GL_FRAGMENT_SHADER);
	linkAndRun();
}
bool ShaderProgram::addProgram(const char * filePath, unsigned short shaderType) {
	qDebug() << "\nAttempting to load file: " << filePath;
	
	bool isValid = validFile(filePath);
	if(isValid) {
		CodeBlock shaderInfo;
		shaderInfo.code = file2str(filePath);
		shaderInfo.id = glCreateShader(shaderType);
		qDebug() << "File Load Successful ID: " << shaderInfo.id;

		isValid = complileShader(shaderInfo.code.c_str(),shaderInfo.id,true);
		if(isValid) {
			glAttachShader(programID,shaderInfo.id);
			qDebug() << "File(" << shaderInfo.id << ") Complile Successful ProgramID: " << programID << "\n";
		} else {
			qDebug() << "File(" << shaderInfo.id << ") Failed to Complile - NOT ADDED TO PROGRAM\n";
		}
	}
	return isValid;
}

int ShaderProgram::getUniform(const char* title) {
	return glGetUniformLocation(getProgramID(),title);
}

void ShaderProgram::passUniform(const char* name, ParameterType parameterType, const float * value) {
	uint location = getUniform(name);
	if(parameterType == ParameterType::PT_FLOAT) {
		glUniform1f(location, *value);
	} else if(parameterType == ParameterType::PT_VEC2) {
		glUniform2fv(location,1,value);
	} else if(parameterType == ParameterType::PT_VEC3) {
		glUniform3fv(location,1,value);
	} else if(parameterType == ParameterType::PT_VEC4) {
		glUniform4fv(location,1,value);
	} else if(parameterType == ParameterType::PT_MAT3) {
		glUniformMatrix3fv(location,1,false,value);
	} else if(parameterType == ParameterType::PT_MAT4) {
		glUniformMatrix4fv(location,1,false,value);
	} else {
		//wat?
	}
}
void ShaderProgram::passUniform(const char* name, ParameterType parameterType, const int value) {
	uint location = getUniform(name);

	if(parameterType == ParameterType::PT_TEXTURE || ParameterType::PT_BOOLEAN) {
		glUniform1i(location,value);
	} else {
		//wat?
	}
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

void ShaderProgram::link() {
	qDebug() << "Linking Program ID: " << programID;
	glLinkProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
	return programID;
}
GLuint ShaderProgram::getCurrentlyUsedProgram() {
	return currentProgram;
}
bool ShaderProgram::isCurrentProgram() {
	return (currentProgram == programID);
}
void ShaderProgram::useProgram() {
	if(!isCurrentProgram()) {
		qDebug() << "Regestering Shader Program " << programID << " into pipeline\n\n";
		currentProgram = programID;
		glUseProgram(programID);
	}
}

GLuint ShaderProgram::linkAndRun() {
	link();
	useProgram();
	return programID;
}


QImage ShaderProgram::getImageFromFile(QString filePath) {
	QString fileName = QCoreApplication::applicationDirPath() + filePath;
	QImage myTexture = QGLWidget::convertToGLFormat(QImage(fileName));

	if(myTexture.isNull()) {
		qDebug() << "attempt to load " << fileName << " failed";
	}
	return myTexture;
}
//returns the bufferID
GLuint ShaderProgram::load2DTexture(QString filePath) {
	
	static uint textureID = 0;

	uint ID = textureID++;

	GLuint bufferID;

	QImage data = getImageFromFile(filePath);

	glActiveTexture(GL_TEXTURE0+ID);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1,&bufferID);

	glBindTexture(GL_TEXTURE_2D, bufferID);

	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, data.width(), data.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return ID;
}