#include "BinaryVertShapeData.h"
#include <fstream>
#include <Windows.h>
#include <cassert>

void BinaryVertShapeData::loadFromFile(char * filename) {
	std::ifstream input( filename , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	int ByteSize = input.tellg();
	input.seekg(0, std::ios::beg);
}