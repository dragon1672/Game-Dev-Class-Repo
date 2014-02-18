#pragma once

#include "Renderable.h"
#include "GeometryInfo.h"
#include "ShaderProgram.h"
#include "ShaderUniformPram.h"
#include "ParameterType.h"


class Renderer {
private:
	Renderable myRenderables[200];
	uint numOfRenderables;
public:
	ShaderProgram * mainShader;
private:
	ShaderProgram allShaderProgs[10];
	uint numOfShaders;

	GeometryInfo geoInfo[100];
	uint numOfGeoInfo;
public:
	void init();

	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode);

	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID);

	ShaderProgram * addShader();
	ShaderProgram * addShader(const char * vertexShader, const char * fragShader);

	uint getNumOfShaders();
	uint getNumOfRenderables();
	uint getNumOfGeo();
	ShaderProgram * getShader(uint index);
	Renderable* getRenderable(uint index);
	GeometryInfo* getGeometry(uint index);

	//not required
	void addStreamedParameter(GeometryInfo * geoID, uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);

	//not required
	void addRenderableUniformParameter(Renderable* renderable, const char* name, ParameterType parameterType, const float* value);

	uint addTexture(const char* fileName);
	void draw(GeometryInfo& toDraw);
};