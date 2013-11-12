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
void SolarSystem::update(float dt) {
	orbitAngle+=orbitAcc*dt;
	for (unsigned int i=0; i<children.size(); i++)
		children[i]->update(dt);
}
void SolarSystem::draw(Core::Graphics graphics,const Matrix3D& transform) {
	//*
	//graphics.DrawLine(0,0,inRefTo.getX(),inRefTo.getY());

	Matrix3D result = transform * Matrix3D::rotationMatrix(orbitAngle) * Matrix3D::translate(Vector2D(0,orbitLength));
	thisStyle.draw(graphics,result * Matrix3D::scale(.5));
	for (unsigned int i=0; i<children.size(); i++)
		children[i]->draw(graphics,result);
	//*/
}

const float scaleDecrease = 2;
const float startScale = 1;
void SolarSystem::startup(int depth) {
	depth;
	/*
	SolarSystem *one = new SolarSystem();
	SolarSystem *two = new SolarSystem();
	SolarSystem *thr = new SolarSystem();
	addChild(one);
	one->addChild(two);
	two->addChild(thr);//*/
	//*
	SolarSystem *toAdd = new SolarSystem[depth];
	for(int i=0;i<depth;i++) {
		if(i>0) {
			toAdd[i].orbitLength = toAdd[i-1].orbitLength-2;
			toAdd[i].orbitAcc    = toAdd[i-1].orbitAcc;//-.5f;
		}

		toAdd[i].size = 1;//startScale - i*scaleDecrease;
		if(i>0) toAdd[i].addChild(&toAdd[i-1]);
		////addChild(&toAdd[i]);
	}
	addChild(&toAdd[depth-1]);
	//*/
}