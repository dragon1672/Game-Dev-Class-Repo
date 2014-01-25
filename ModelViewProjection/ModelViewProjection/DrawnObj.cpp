#include <GL\glew.h>

#include "DrawnObj.h"


uint DrawnObj::dataOffset() {
	return startOffset;
}
uint DrawnObj::indicesOffset() {
	return startOffset + vertexBufferSize();
}
uint DrawnObj::endOffset() {
	return vertexBufferSize() + indexBufferSize();
}
uint DrawnObj::totalBufferSize() {
	return indexBufferSize() + vertexBufferSize();
}

void DrawnObj::copyFromShape(ShapeData toCopy) {
	this->verts		 = toCopy.verts;
	this->numVerts	 = toCopy.numVerts;
	this->indices	 = toCopy.indices;
	this->numIndices = toCopy.numIndices;
}
void DrawnObj::init(ShapeData toCopy, uint previousOffset) {
	copyFromShape(toCopy);
	startOffset = previousOffset;
}
void DrawnObj::sendToBuffer(uint bufferID) {

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	
	glBufferSubData(GL_ARRAY_BUFFER,dataOffset(),vertexBufferSize(),verts);
	glBufferSubData(GL_ARRAY_BUFFER,indicesOffset(),indexBufferSize(),indices);

	glGenVertexArrays(1,&vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(dataOffset() + Neumont::Vertex::POSITION_OFFSET));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Neumont::Vertex::STRIDE, (void*)(dataOffset() + Neumont::Vertex::COLOR_OFFSET));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}
void DrawnObj::printPrep() {
	glBindVertexArray(vertexArrayObjectID);
}
void DrawnObj::cleanUp() {
	delete[] verts;
	verts = 0;
	delete[] indices;
	indices = 0;
	//numVerts = numIndices = 0;
}
