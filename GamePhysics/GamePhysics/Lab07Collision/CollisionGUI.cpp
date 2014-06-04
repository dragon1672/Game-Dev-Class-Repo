#include "CollisionGUI.h"

void CollisionGUI::init() {
	PhysicsGUIBase::init();
	mouseDragTimer.start();
	numOfNodes = 0;
	collisionData.restitution = 1;
	for (int i = 0; i < 2; i++)
	{
		collisionData.particle[i] = &allPoints[i].point;

		allPoints[i].point.init(1,(i==0)? .5 : .3);
		allPoints[i].point.pos = (i==0) ? glm::vec3(-3,0,0) : glm::vec3(3,0,0);
		allPoints[i].pointGraphic = addVectorGraphic();
		allPoints[i].startVel = (i==0) ? glm::vec3(2,0,0) : glm::vec3(-3,0,0);
			allPoints[i].pointGraphic->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(0,0,1);
		allPoints[i].vel= addVectorGraphic();
			allPoints[i].vel->displayStyle = DS_ARROW;
			allPoints[i].vel->color = (i==0) ? glm::vec3(1,0,0) : glm::vec3(1,0,0);
		allPoints[i].mom= addVectorGraphic();
			allPoints[i].mom->displayStyle = DS_ARROW;
			allPoints[i].mom->color = glm::vec3(0,0,1);
		allPoints[i].collideVel= addVectorGraphic();
			allPoints[i].collideVel->displayStyle = DS_ARROW;
			allPoints[i].collideVel->color = glm::vec3(0,1,0);
		numOfNodes++;
	}
	systemMomGraphic = addVectorGraphic();
	systemMomGraphic->displayStyle = DS_ARROW;
	systemMomGraphic->color = glm::vec3(0,0,1);

	collisionManager.init(&allPoints[0].point,&allPoints[1].point);

	reset();
		
	myDebugMenu.button("Factory Reset (1D)", fastdelegate::MakeDelegate(this,&CollisionGUI::factoryReset));
	myDebugMenu.button("Factory Reset (2D)", fastdelegate::MakeDelegate(this,&CollisionGUI::reset2D));
	myDebugMenu.button("Reset Particles (Sliders)", fastdelegate::MakeDelegate(this,&CollisionGUI::reset));
	myDebugMenu.button("Cause Collision", fastdelegate::MakeDelegate(this,&CollisionGUI::collide));
	myDebugMenu.edit("Red Mass",  allPoints[0].point.mass, 0.0f, 5.0f);
	myDebugMenu.edit("Blue Mass", allPoints[1].point.mass, 0.0f, 5.0f);
	myDebugMenu.edit("Restitution", collisionData.restitution, 0, 1);
	myDebugMenu.edit("Red Initial Vel", allPoints[0].startVel, 0,  10, -5, 5, 0, 0);
	myDebugMenu.edit("Blu Initial Vel", allPoints[1].startVel, 0, -10, -5, 5, 0, 0);
	myDebugMenu.watch("Red Vel", allPoints[0].point.vel);
	myDebugMenu.watch("Blu Vel", allPoints[1].point.vel);
	myDebugMenu.watch("System Momentum",systemMom);
	myDebugMenu.watch("Total Kinetic Energy",totalKineticEnergy);
};
void CollisionGUI::factoryReset() {
	allPoints[0].point.init(1,.5f);
	allPoints[0].point.pos = glm::vec3(-3,0,0);
	allPoints[0].startVel = glm::vec3(2,0,0);
	allPoints[1].point.init(1,.3f);
	allPoints[1].point.pos = glm::vec3(3,0,0);
	allPoints[1].startVel = glm::vec3(-3,0,0);
	reset();
}
void CollisionGUI::reset() {
	allPoints[0].point.pos = glm::vec3(-3,0,0);
	allPoints[0].point.vel = allPoints[0].startVel;
	allPoints[1].point.pos = glm::vec3(3,0,0);
	allPoints[1].point.vel = allPoints[1].startVel;
}
void CollisionGUI::reset2D() {
	allPoints[0].point.mass = 3.5f;
	allPoints[1].point.mass = 1.3f;
	allPoints[0].point.pos  = glm::vec3(-5,0,0);
	allPoints[0].startVel   = glm::vec3(1.5,1,0);
	allPoints[1].point.pos  = glm::vec3(5,0,0);
	allPoints[1].startVel   = glm::vec3(-1.5,1,0);

	allPoints[0].point.vel = allPoints[0].startVel;
	allPoints[1].point.vel = allPoints[1].startVel;
}
void CollisionGUI::newFrame() {
	PhysicsGUIBase::newFrame();
		
	if(mouseDragTimer.stop() > dt()*10) {
		collisionManager.update();
			
		systemMom = glm::vec3();
		totalKineticEnergy = 0;
			
		for (int i = 0; i < numOfNodes; i++)
		{
			allPoints[i].point.update(dt());
			systemMom += allPoints[i].point.momentum;
			totalKineticEnergy += .5 * allPoints[i].point.mass * glm::dot(allPoints[i].point.vel,allPoints[i].point.vel);
		}

		if(collisionManager.hasCollided()) {
			collide();
		}
		for (int i = 0; i < numOfNodes; i++)
		{
			allPoints[i].point.clearForce();
		}
	}

	redraw();
}
void CollisionGUI::collide() {
	collisionData.contactNormal = collisionManager.getNormal();
	collisionData.penetration = collisionManager.getPenetration();
	collisionData.collide(dt());
}
void CollisionGUI::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	mouseDragTimer.start();
	int index = vectorGraphicIndex / 4; // 2 graphics made for each point
	allPoints[index].point.pos += dragDelta;

	collisionManager.update();

	redraw();
}
void CollisionGUI::redraw() {
	for (int i = 0; i < numOfNodes; i++)
	{
		allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
		syncVector(allPoints[i].pointGraphic,allPoints[i].point.pos);
		syncVector(allPoints[i].vel,allPoints[i].point.vel,allPoints[i].point.pos);
		syncVector(allPoints[i].mom,allPoints[i].point.momentum,allPoints[i].point.pos);
		syncVector(allPoints[i].collideVel,collisionManager.vels[i],allPoints[i].point.pos);
		syncVector(systemMomGraphic,systemMom);
	}
}