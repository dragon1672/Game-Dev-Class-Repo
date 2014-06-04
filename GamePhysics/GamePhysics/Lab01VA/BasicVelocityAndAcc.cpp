#include "BasicVelocityAndAcc.h"


void BasicVelocityAndAcc::init() {
	SingleParticleGui::init();
}
void BasicVelocityAndAcc::newFrame() {
	float acc = 1;
	glm::vec3& pos = myParticle.pos;
	glm::vec3& vel = myParticle.vel;
	vel += acc * dt() * getUserDirection();
	pos += vel * dt();
	sync(particalGraphic,pos);
	sync(velGraphic,vel,pos);
}
void BasicVelocityAndAcc::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	glm::vec3& pos = myParticle.pos;
	glm::vec3& vel = myParticle.vel;
	pos += dragDelta;
	vel += dragDelta / 1.0f;
	sync(particalGraphic,pos);
	sync(velGraphic,vel,pos);
}