#pragma once
#include <ShapeData.h>

struct DrawnObj : public Neumont::ShapeData {
	uint startOffset;
	uint vertexArrayObjectID;
	uint dataOffset();
	uint indicesOffset();
	uint endOffset();
	uint totalBufferSize();

	void copyFromShape(ShapeData toCopy);
	void init(ShapeData toCopy, uint previousOffset=0);
	void sendToBuffer(uint bufferID);
	void printPrep();
	//override
	void cleanUp();
};