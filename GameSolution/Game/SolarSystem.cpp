#include "SolarSystem.h"
#include "Matrix3D.h"
#include <cassert>
const float anglesInCircle = 2*3.14f;
Core::RGB color = RGB(100,255,0);
Shape SolarSystem::thisStyle(color,
							3,
							Vector2D(-5,-2),
							Vector2D( 5,-2),
							Vector2D( 0,13)
							);


void SolarSystem::addChild(SolarSystem *toAdd) {
	children.push_back(toAdd);
}
/*I was a bit confused about how this section was working, changing this or adding comments would help*/
void SolarSystem::update(float dt) {
	orbitAngle+=orbitAcc*dt;
	for (unsigned int i=0; i<children.size(); i++)
		children[i]->update(dt);
}
void SolarSystem::draw(Core::Graphics graphics,const Matrix3D& transform) {
	Matrix3D result = transform * Matrix3D::rotationMatrix(orbitAngle) * Matrix3D::translate(Vector2D(0,orbitLength));
	thisStyle.draw(graphics,result * Matrix3D::scale(size));
	for (unsigned int i=0; i<children.size(); i++)
		children[i]->draw(graphics,result);
}

void SolarSystem::startup(int depth) {
	const float targetSize = .2f;
	const float targetAcc  = 5;
	const float targetLen  = 10;
	SolarSystem *toAdd = new SolarSystem[depth];//memory leak
	float lengthDecrease = (toAdd[0].orbitLength -  targetLen ) / depth;
	float accDecrease    = (toAdd[0].orbitAcc    -  targetAcc ) / depth;
	float sizeDecrease   = (toAdd[0].size        -  targetSize) / depth;
	for(int i=1;i<depth;i++) {
		toAdd[i].orbitLength = toAdd[0].orbitLength - i*lengthDecrease;
		toAdd[i].orbitAcc    = toAdd[0].orbitAcc    - i*accDecrease;
		toAdd[i].size        = toAdd[0].size        - i*sizeDecrease;
		toAdd[i-1].addChild(&toAdd[i]);
	}
	addChild(toAdd);
	//*/
}