#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "CubeSolarSystem.h"
#include "Randomness.h"

glm::vec3 CubeSolarSystem::orbitLength(0,0,0);
glm::vec3 CubeSolarSystem::orbitAxis(100,100,100);
float CubeSolarSystem::orbitAcc = 3;

void CubeSolarSystem::randomAcc() {
	xAngleAcc = Random::randomFloat(-2,2);
	yAngleAcc = Random::randomFloat(-2,2);
	zAngleAcc = Random::randomFloat(-2,2);
}
void CubeSolarSystem::update(int frames) {
	orbitAngle += orbitAcc;

	xAngle += xAngleAcc;
	yAngle += yAngleAcc;
	zAngle += zAngleAcc;

	if(frames%100==0) {
		randomAcc();
	}
}

glm::mat4x4 CubeSolarSystem::getTransform() {
	glm::mat4x4 transform;
	transform *= glm::rotate(xAngle,glm::vec3(1,0,0));
	transform *= glm::rotate(yAngle,glm::vec3(0,1,0));
	transform *= glm::rotate(zAngle,glm::vec3(0,0,1));
	return transform;
}

void CubeSolarSystem::draw(int transformLocation,glm::mat4x4 lastTransform,int vertCount, void * offset, float scale, int depth, int children) {
	if(depth>=0) {
		float averageAngle = 360.0f/children;
		for (int i = 0; i < children; i++)
		{
			//glm::vec4 previousTranslation = lastTransform * glm::vec4(0,0,0,0);
			//glm::mat4x4 transform = glm::translate(glm::vec3(previousTranslation));
			glm::mat4x4 transform =lastTransform;
			transform *= glm::rotate(orbitAngle + i*averageAngle,orbitAxis);
			transform *= glm::translate(scale * orbitLength);
			transform *= getTransform();

			glm::mat4x4 toDraw = transform *= scale * glm::scale(orbitAxis);
			glUniformMatrix4fv(transformLocation,1,false,&toDraw[0][0]);
			glDrawElements(GL_TRIANGLES,vertCount,GL_UNSIGNED_SHORT,offset);

			draw(transformLocation,transform,vertCount,offset,.6f * scale,depth-1,children);
		}
	}
}