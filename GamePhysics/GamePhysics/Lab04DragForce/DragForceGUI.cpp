#include "DragForceGUI.h"


void DragForceGUI::init() {
	SingleParticleGui::init();
	myParticle.init(1,1);
	myDrag.init();
	myGrav.dir = glm::vec3(0,-1,0);
	myKeyboard.init(keyboardInput);

	enableDrag = true;
	enableDrag_last = false;

	lowDragGraphic  = addVectorGraphic();
	highDragGraphic = addVectorGraphic();
	lowDragGraphic  -> displayStyle = DS_ARROW;
	highDragGraphic -> displayStyle = DS_ARROW;
	lowDragGraphic  -> color = glm::vec3(0,.7,0);
	highDragGraphic -> color = glm::vec3(0,1,1);

	resetParticle();
		
	//debug menus
	myDebugMenu.slideFloat("Mass",myParticle.mass,  .1f, 10);
	myDebugMenu.slideFloat("Drag High",myDrag.high,   0,  5);
	myDebugMenu.slideFloat("Drag Low", myDrag.low,    0,  5);
	myDebugMenu.watchVector("Momentum",myParticle.momentum);
	myDebugMenu.watchVector("Velocity",myParticle.vel);
	myDebugMenu.watchVector("Position",myParticle.pos);
	myDebugMenu.toggleBool("Enable Gravity",enableGrav);
	myDebugMenu.toggleBool("Enable KeyBoard Force",enableKey);
	myDebugMenu.toggleBool("Enable Drag Force",enableDrag);
}
void DragForceGUI::newFrame() {
	SingleParticleGui::newFrame();
	keyboardInput = getUserDirection() * 2.0f;
		
	updateForces();
	forceManager.updateForces();

	myParticle.update(dt());
	myParticle.clearForce();

	particalGraphic->pointSize = myParticle.mass;

	if(glm::dot(myParticle.vel,myParticle.vel)<.2
		|| myParticle.vel.x < 0
		|| myParticle.pos.x > 5
		|| myParticle.pos.y < -2
		|| myParticle.pos.y > 5
		) {
		resetParticle();
	}

	syncBaseVectors();
	syncVector(lowDragGraphic, myDrag.lowForce, myParticle.pos);
	syncVector(highDragGraphic,myDrag.highForce,myParticle.pos);
}
void DragForceGUI::updateForces() {
	if(enableGrav != enableGrav_last) {
		enableGrav ? forceManager.add(&myParticle,&myGrav) : forceManager.remove(&myParticle,&myGrav);
	}
	if(enableKey != enableKey_last) {
		enableKey ? forceManager.add(&myParticle,&myKeyboard) : forceManager.remove(&myParticle,&myKeyboard);
	}
	if(enableDrag != enableDrag_last) {
		enableDrag ? forceManager.add(&myParticle,&myDrag) : forceManager.remove(&myParticle,&myDrag);
		myDrag.highForce = glm::vec3();
		myDrag.lowForce = glm::vec3();
	}
	enableGrav_last = enableGrav;
	enableKey_last  = enableKey;
	enableDrag_last = enableDrag;
}
void DragForceGUI::resetParticle() {
	myParticle.pos = glm::vec3(-3,3,0);
	myParticle.vel = glm::vec3(8,0,0);
}