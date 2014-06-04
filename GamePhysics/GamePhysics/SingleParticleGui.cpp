#include "SingleParticleGui.h"


void SingleParticleGui::init() {
	PhysicsGUIBase::init();
	particalGraphic = addVectorGraphic();
	particalGraphic->color = glm::vec3(.5,.5,.5);
	velGraphic = addVectorGraphic();
	velGraphic->displayStyle = DS_ARROW;
	velGraphic->color = glm::vec3(1,0,0);
	momentumGraphic = addVectorGraphic();
	momentumGraphic->displayStyle = DS_ARROW;
	momentumGraphic->color = glm::vec3(0,0,1);
}
void SingleParticleGui::syncBaseVectors() {
	syncVector(particalGraphic,myParticle.pos);
	syncVector(velGraphic,myParticle.vel,myParticle.pos);
	syncVector(momentumGraphic,myParticle.momentum,myParticle.pos);
}