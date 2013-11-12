#include "SolarSystem.h"
#include "Matrix3D.h"
#include <cassert>
const float anglesInCircle = 2*3.14;
Core::RGB color = RGB(100,255,0);
Shape SolarSystem::thisStyle(color,
							3,
							5*Vector2D(-5,-2),
							5*Vector2D( 5,-2),
							5*Vector2D( 0,13)
							);


void SolarSystem::addChild(const SolarSystem& toAdd) {
	children.push_back(toAdd);
}
void SolarSystem::update(float dt) {
	orbitPercent+=orbitAcc*dt;
	for (std::vector<SolarSystem>::iterator it = children.begin(); it != children.end(); ++it) {
		it->update(dt);
	}
}
void SolarSystem::draw(Core::Graphics graphics,const Vector2D& inRefTo) {
	Matrix3D transform = Matrix3D::translate(inRefTo) * Matrix3D::rotationMatrix(anglesInCircle/orbitPercent) * Matrix3D::translate(Vector2D(0,orbitLength)) * Matrix3D::scale(scale);
	Vector2D myPos = transform * myPos;
	thisStyle.draw(graphics,transform);
	for (std::vector<SolarSystem>::iterator it = children.begin(); it != children.end(); ++it) {
		it->draw(graphics,myPos);
	}
}

const float scaleDecrease = 5;
const int maxDepthOfSolarSystems = 10;
const float startScale = 100;
void SolarSystem::startup(int depth) {
	assert(depth<maxDepthOfSolarSystems);
	SolarSystem toAdd[maxDepthOfSolarSystems];
	for(int i=0;i<depth;i++) {
		toAdd[i].scale = startScale - i*scaleDecrease;
		if(i>0) toAdd[i-1].addChild(toAdd[i]);
	}
}