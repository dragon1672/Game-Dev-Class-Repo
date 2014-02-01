#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_h

#include <QtOpenGL\qglwidget>
#include <string>
#include <unordered_map>

class ShaderProgram {
private:
	static const int MAX_POSSIBLE_PROGRAM_FILES = 10;
	struct CodeBlock { // used to store shader code
		GLuint id;
		std::string code;
	};

	std::unordered_map<char*, int> uniforms;

	CodeBlock blocks[MAX_POSSIBLE_PROGRAM_FILES];
	int numOfFiles;
	
	GLuint programID;

	std::string file2str(const char * filePath);
	bool validFile(const char * filePath);
public:
	void startup();
	void shutdown();
	bool addProgram(const char * filePath, unsigned short shaderType);

	int generateUniform(char* title);
	int getUniform(char* title);

	bool complileShader(const char * code, GLuint id, bool debug);
	void compileAndLink();

	GLuint getProgramID();
	void useProgram();

	GLuint compileAndRun();
};

#endif