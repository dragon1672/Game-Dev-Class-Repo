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
void SolarSystem::draw(Core::Graphics graphics,const Vector2D& inRefTo) {
	Matrix3D transform = Matrix3D::rotationMatrix(orbitAngle) * Matrix3D::translate(Vector2D(0,orbitLength));
	Vector2D myTranPos = transform * inRefTo;//Vector2D(0,0);
	thisStyle.draw(graphics,Matrix3D::translate(inRefTo) * transform);
	for (unsigned int i=0; i<children.size(); i++)
		children[i]->draw(graphics,myTranPos);
}

const float scaleDecrease = 2;
const float startScale = 1;
void SolarSystem::startup(int depth) {
	depth;
	//*
	SolarSystem *one = new SolarSystem();
	SolarSystem *two = new SolarSystem();
	SolarSystem *thr = new SolarSystem();
	addChild(one);
	one->addChild(two);
	two->addChild(thr);//*/
	/*
	SolarSystem *toAdd = new SolarSystem[depth];
	for(int i=0;i<depth;i++) {
		toAdd[i].size = 2;//startScale - i*scaleDecrease;
		if(i>0) toAdd[i].addChild(&toAdd[i-1]);
		////addChild(&toAdd[i]);
	}
	addChild(&toAdd[0]);
	//*/
}