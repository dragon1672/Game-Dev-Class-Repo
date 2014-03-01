#pragma once

#include "ShapeData.h"

class BinaryToShapeLoader {
public:
	static Neumont::ShapeData loadFromFile(const char * filePath);
};