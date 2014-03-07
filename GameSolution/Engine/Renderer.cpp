#include <GL/glew.h>

#include "Renderer.h"

void            Renderer::init() {
	numOfRenderables = 0;
	numOfShaders = 0;
	numOfGeoInfo = 0;
	mainShader = addShader();
}
GeometryInfo *  Renderer::addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode) {
	int id = numOfGeoInfo++;
	geoInfo[id].init(verts,numVerts,indices,numIndices,indexingMode);
	return &geoInfo[id];
}
Renderable*     Renderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID) {
	int id = numOfRenderables++;
	myRenderables[id].init(whatGeometry,howShaders,true,textureID);
	return &myRenderables[id];
}
ShaderProgram * Renderer::addShader() {
	return &allShaderProgs[numOfShaders++];
}
ShaderProgram * Renderer::addShader(const char * vertexShader, const char * fragShader) {
	ShaderProgram * ret = addShader();
	ret->buildBasicProgram(vertexShader,fragShader);
	return ret;
}
uint            Renderer::getNumOfShaders()      { return numOfShaders;     }
uint            Renderer::getNumOfRenderables()  { return numOfRenderables; }
uint            Renderer::getNumOfGeo()          { return numOfGeoInfo;     }
ShaderProgram * Renderer::getShader(uint index) { return &allShaderProgs[index]; }
Renderable*     Renderer::getRenderable(uint index) { return &myRenderables[index];  }
GeometryInfo*   Renderer::getGeometry(uint index) { return &geoInfo[index];        }
void            Renderer::addStreamedParameter(GeometryInfo * geoID, uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride) {
	geoID->addStreamedParameter(layoutLocation,parameterType,bufferOffset,bufferStride);
}
void            Renderer::addRenderableUniformParameter(Renderable* renderable, const char* name, ParameterType parameterType, const float* value) {
	renderable->addUniformParameter(name,parameterType,value);
}
uint            Renderer::addTexture(const char* fileName) {
	return ShaderProgram::load2DTexture(fileName);
}
void            Renderer::draw(GeometryInfo& toDraw) {
	glBindVertexArray(toDraw.vertexArrayObjectID);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ARRAY_BUFFER);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(toDraw.indexingMode,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
}
void            Renderer::drawPrep() {
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}