#include "Renderable.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "MyRandom.h"

void Renderable::init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID) {
	this->whatGeo   = whatGeo;
	this->howShader = howShader;
	this->visible   = visible;
	this->textureID = textureID;
	randomRange = DEFAULT_RANGE;
	randomACC();
	scale = 1;
	numUniformParameters = 0;
	translate = glm::vec3();
	angles = glm::vec3();
}

void Renderable::setScale(float scale) {
	this->scale = scale;
}
void Renderable::setTranslate(glm::vec3 toTrans) {
	translate = toTrans;
	recalcTransformAndRotation();
}
void Renderable::addTranslate(glm::vec3 toTrans) {
	translate += toTrans;
	recalcTransformAndRotation();
}

void Renderable::rotate() {
	angles += angleAcc;
	recalcTransformAndRotation();
}
void Renderable::randomACC() {
	randomACC(-randomRange, randomRange);
}
void Renderable::randomACC(float lowRange, float upperRange) {
	angleAcc.x = RANDOM::randomFloat(lowRange,upperRange);
	angleAcc.y = RANDOM::randomFloat(lowRange,upperRange);
	angleAcc.z = RANDOM::randomFloat(lowRange,upperRange);
}

void Renderable::recalcTransformAndRotation() {
	rotation = glm::mat3( glm::rotate(angles.x,glm::vec3(1,0,0))
						* glm::rotate(angles.y,glm::vec3(0,1,0))
						* glm::rotate(angles.z,glm::vec3(0,0,1)));
	whereMat = glm::translate(translate)
			 * glm::mat4(rotation)
			 * glm::scale(glm::vec3(scale,scale,scale));
}

void Renderable::addUniformParameter(const char * name, ParameterType parameterType, const float * value) {
	uniformParameters[numUniformParameters++].init(howShader,name,parameterType,value);
}
void Renderable::addUniformParameter(const char * name, ParameterType parameterType, const int * value) {
	uniformParameters[numUniformParameters++].init(howShader,name,parameterType,value);
}
void Renderable::saveWhereMat(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_MAT4,(float*)&whereMat[0]);
}
void Renderable::saveRotationMat(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_MAT3,(float*)&rotation[0]);
}
void Renderable::saveTexture(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_TEXTURE,(int*)&textureID);
}
void Renderable::saveVisable(const char * uniformName) {
	addUniformParameter(uniformName,ParameterType::PT_BOOLEAN,(int*)&visible);
}

void Renderable::passUniformsDownDown() {
	for (uint i = 0; i < numUniformParameters; i++)
	{
		uniformParameters[i].sendData();
	}
}