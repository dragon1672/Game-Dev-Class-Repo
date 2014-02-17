#pragma once

#include "ShaderProgram.h"
#include "ParameterType.h"
#include <string>

typedef unsigned int uint;

class ShaderUniformPram {
private:
	ParameterType type;
	const char * title;
	ShaderProgram * theProg;
public:
	const float * cashedFloat;
	const int * cashedInt;

	void init(ShaderProgram * prog, const char * name, ParameterType type);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const int * val);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const float * val);

	void sendData();
	void sendData(const int * val);
	void sendData(const float * val);
};