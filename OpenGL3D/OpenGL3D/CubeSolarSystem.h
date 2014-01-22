#pragma once
#include <glm\glm.hpp>

struct CubeSolarSystem {
	static glm::vec3 orbitLength;
	static glm::vec3 orbitAxis;

	float orbitAngle;
	static float orbitAcc;

	float xAngle;
	float xAngleAcc;
	float yAngle;
	float yAngleAcc;
	float zAngle;
	float zAngleAcc;

	CubeSolarSystem() {
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		randomAcc();
	}
	void randomAcc();
	void update(int frames);
	glm::mat4x4 getTransform();
	void draw(int transformLocation,glm::mat4x4 lastTransform,int vertCount, void * offset, float scale, int depth, int children);
};