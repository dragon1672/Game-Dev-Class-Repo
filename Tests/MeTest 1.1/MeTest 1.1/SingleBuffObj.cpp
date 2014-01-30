#include <GL\glew.h>

#include "SingleBuffObj.h"


uint SingleBuffObj::dataOffset() {
	return startOffset;
}
uint SingleBuffObj::indicesOffset() {
	return startOffset + vertexBufferSize();
}
uint SingleBuffObj::endOffset() {
	return startOffset + totalBufferSize();
}
uint SingleBuffObj::totalBufferSize() {
	return indexBufferSize() + vertexBufferSize();
}

void SingleBuffObj::copyFromShape(ShapeData toCopy) {
	this->verts		 = toCopy.verts;
	this->numVerts	 = toCopy.numVerts;
	this->indices	 = toCopy.indices;
	this->numIndices = toCopy.numIndices;
}
void SingleBuffObj::init(ShapeData toCopy, uint previousOffset) {
	copyFromShape(toCopy);
	startOffset = previousOffset;
}
void SingleBuffObj::sendToBuffer(uint bufferID) {

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	
	glBufferSubData(GL_ARRAY_BUFFER,dataOffset(),vertexBufferSize(),verts);
	glBufferSubData(GL_ARRAY_BUFFER,indicesOffset(),indexBufferSize(),indices);


	//glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glGenVertexArrays(1,&vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID); // dont understand why we need multiple of these
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(dataOffset() + Neumont::Vertex::POSITION_OFFSET));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(dataOffset() + Neumont::Vertex::COLOR_OFFSET));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); // dont understand why we need multiple of these
}
void SingleBuffObj::printPrep() {
	glBindVertexArray(vertexArrayObjectID);
}
void SingleBuffObj::cleanUp() {
	delete[] verts;
	verts = 0;
	delete[] indices;
	indices = 0;
	//numVerts = numIndices = 0;
}
