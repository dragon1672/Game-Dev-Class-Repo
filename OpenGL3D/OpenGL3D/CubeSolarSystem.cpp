#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "CubeSolarSystem.h"
#include "Randomness.h"

glm::vec3 CubeSolarSystem::orbitAxis(0,0,1);
glm::vec3 CubeSolarSystem::orbitLength(0,10,0);
float CubeSolarSystem::orbitAcc = .5;

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

void CubeSolarSystem::draw(CubeSolarSystem * blockData, int transformLocation,glm::mat4x4 lastTransform,int vertCount, void * offset, float scale, int depth, int children, glm::vec3 orbitLength, glm::vec3 orbitAxis) {
	if(depth>=0) {
		float averageAngle = 360.0f/children;
		for (int i = 0; i < children; i++)
		{
			//glm::vec4 previousTranslation = lastTransform * glm::vec4(0,0,0,0);
			//glm::mat4x4 transform = glm::translate(glm::vec3(previousTranslation));
			glm::mat4x4 transform = glm::rotate(orbitAngle + i*averageAngle,orbitAxis)
									* glm::translate(scale * orbitLength)
									* glm::scale(glm::vec3(scale,scale,scale));

			//transform = glm::translate(glm::vec3(previousTranslation)) * transform;
			transform = lastTransform * transform;

			glm::mat4x4 toDraw = transform * blockData->getTransform();
			glUniformMatrix4fv(transformLocation,1,false,&toDraw[0][0]);
			glDrawElements(GL_TRIANGLES,vertCount,GL_UNSIGNED_SHORT,offset);

			draw(blockData+1, transformLocation,transform,vertCount,offset,.6f * scale,depth-1,children);
		}
	}
}