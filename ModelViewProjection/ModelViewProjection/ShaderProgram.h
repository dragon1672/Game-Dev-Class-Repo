#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_h

#include <QtOpenGL\qglwidget>
#include <string>
#include "ParameterType.h"

class ShaderProgram {
private:
	static const int MAX_POSSIBLE_PROGRAM_FILES = 10;
	static GLuint currentProgram;
	
	GLuint programID;

	static std::string file2str(const char * filePath);
	static bool validFile(const char * filePath);
public:
	void startup();
	void shutdown();

	//restarts, compiles, link and uses this program
	void buildBasicProgram(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	bool addProgram(const char * filePath, unsigned short shaderType);

	int getUniform(const char* title);
	void passUniform(const char* name, ParameterType parameterType, const float * value);
	void passUniform(const char* name, ParameterType parameterType, const int value);

	bool complileShader(const char * code, GLuint id, bool debug);
	void link();

	GLuint getProgramID();
	GLuint getCurrentlyUsedProgram();
	bool isCurrentProgram();
	void useProgram();

	GLuint linkAndRun();

	static QImage getImageFromFile(QString filePath);

	//returns the bufferID
	static GLuint load2DTexture(QString filePath);
};

#endif