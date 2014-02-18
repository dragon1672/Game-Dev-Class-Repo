#include <GL\glew.h>
#include "GeometryInfo.h"

BufferManager GeometryInfo::manager;

void GeometryInfo::init(const Neumont::Vertex * verts, uint numVerts, ushort* indices, uint numIndices, GLuint indexingMode) {
	sizeOfVerts = sizeof(Neumont::Vertex);
	glGenVertexArrays(1,&vertexArrayObjectID);
	this->numVerts = numVerts;
	this->numIndices = numIndices;
	this->indexingMode = indexingMode;
	bufferInformation = manager.addData(vertexBufferSize(),verts,indexBufferSize(),indices);
}

void GeometryInfo::addStreamedParameter(uint layoutLocation, ParameterType parameterType,  uint bufferOffset, uint bufferStride) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferInformation.bufferID);
	glBindVertexArray(vertexArrayObjectID);

	int numOfFloats = parameterType/sizeof(float);

	glEnableVertexAttribArray(layoutLocation); // pos

	glBindBuffer(GL_ARRAY_BUFFER, bufferInformation.bufferID);
	glVertexAttribPointer(layoutLocation, numOfFloats, GL_FLOAT, GL_FALSE, bufferStride, (void*)(bufferOffset+bufferInformation.offset));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferInformation.bufferID);
}