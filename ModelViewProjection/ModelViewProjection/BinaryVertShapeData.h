#pragma once

#include "BinaryVert.h"
typedef unsigned short ushort;

class BinaryVertShapeData {
	BinaryVert * verts;
	uint numVerts;
	ushort* indices;
	uint numIndices;
	BinaryVertShapeData() : verts(0), numVerts(0), indices(0), numIndices(0) {}
	uint vertexBufferSize() const { return numVerts * sizeof(BinaryVert); }
	uint indexBufferSize() const { return numIndices * sizeof(ushort); }
	void loadFromFile(char * filename);
};