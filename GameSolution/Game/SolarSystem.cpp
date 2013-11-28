#include "SolarSystem.h"
#include "Matrix3D.h"
#include <cassert>

Core::RGB color = RGB(100,255,0);
Shape SolarSystem::thisStyle(color,
							3,
							Vector2D(-5,-2),
							Vector2D( 5,-2),
							Vector2D( 0,13)
							);


void SolarSystem::update(float dt) {
	orbitAngle+=orbitAcc*dt;
}
void SolarSystem::draw(MyGraphics& graphics, const Matrix3D& transform, int depth, float scale, int children) {
	if(depth>=0) {
		float averageAngle = anglesInCircle / children;
		for(int i=0;i<children;i++) {
			Matrix3D currentTrans = transform
									* Matrix3D::rotationMatrix(orbitAngle + i * averageAngle)
									* Matrix3D::translate(Vector2D(0,orbitLength*scale));
			thisStyle.draw(graphics,currentTrans * Matrix3D::scale(scale));
			draw(graphics,currentTrans,depth-1,scale*.6f,children);
		}
	}
}
void SolarSystem::draw(MyGraphics& graphics, const Matrix3D& transform) {
	draw(graphics,transform,maxDepth, size, children);//calling private draw
}
void SolarSystem::startup(int depth, int children) {
	maxDepth = depth;
	this->children = children;
}