#pragma once

#include "ShaderUniformPram.h"
#include "GeometryInfo.h"
#include "ExportHeader.h"

#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)

#include "ParameterType.h"

//template struct DLL_SHARED glm::detail::tmat3x3<float>;
//template struct DLL_SHARED glm::detail::tmat4x4<float>;

typedef unsigned int uint;

class ENGINE_SHARED Renderable {
public:
	static const int DEFAULT_RANGE = 5;
	float randomRange;
private:
	ShaderUniformPram uniformParameters[5];
	uint numUniformParameters;
	float scale;
	glm::vec3 translate;
	glm::vec3 angles;
	glm::vec3 angleAcc;
public:
	GeometryInfo * whatGeo;
	ShaderProgram * howShader;
	glm::mat4 whereMat;
	glm::mat3 rotation;
	bool visible;
	uint textureID;

	void init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID);

	void setScale(float scale);
	void setTranslate(glm::vec3 toTrans);
	void addTranslate(glm::vec3 toTrans);
	void rotate();
	void randomACC();
	void randomACC(float lowRange, float upperRange);
	void updateAcc(glm::vec3 newAcc);
	
	void recalcTransformAndRotation();

	void addUniformParameter(const char * name, ParameterType parameterType, const float * value);
	void addUniformParameter(const char * name, ParameterType parameterType, const int * value);
	void saveWhereMat(const char * uniformName);
	void saveRotationMat(const char * uniformName);
	void saveVisable(const char * uniformName);
	void saveTexture(const char * uniformName);
	void passUniformsDownDown();
};