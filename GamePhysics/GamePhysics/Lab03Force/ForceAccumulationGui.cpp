#include "ForceAccumulationGui.h"

void ForceAccumulationGui::init() {
	PhysicsGUIBase::init();
	numOfPoints = 0;
	allPoints[numOfPoints++].point = &one;	one.pos = glm::vec3(-2,0,0);
	allPoints[numOfPoints++].point = &two;
	allPoints[numOfPoints++].point = &thr;	thr.pos = glm::vec3(2,0,0);
		
	for (int i = 0; i < numOfPoints; i++)
	{
		allPoints[i].point->init(1);
		allPoints[i].pointGraphic = addVectorGraphic();
			allPoints[i].pointGraphic->color = glm::vec3(.5,.5,.5);
		allPoints[i].velGraphic   = addVectorGraphic();
			allPoints[i].velGraphic->displayStyle = DS_ARROW;
			allPoints[i].velGraphic->color = glm::vec3(1,0,0);
		allPoints[i].magGraphic   = addVectorGraphic();
			allPoints[i].magGraphic->displayStyle = DS_ARROW;
			allPoints[i].magGraphic->color = glm::vec3(0,0,1);
	}

	keyboardForce.init(keyboardInput);
	gravForce.dir = glm::vec3(0,-1,0);
	forceManager.add(&one,&gravForce);
	forceManager.add(&two,&gravForce);
	forceManager.add(&two,&keyboardForce);
	forceManager.add(&thr,&keyboardForce);

	for (int i = 0; i < numOfPoints; i++)
	{
		myDebugMenu.watchVector("Pos",allPoints[i].point->pos);
		myDebugMenu.watchVector("Vel",allPoints[i].point->vel);
		myDebugMenu.watchVector("Mom",allPoints[i].point->momentum);
		myDebugMenu.slideFloat("Point Mass",allPoints[i].point->mass,.1f,5);

	}
}
void ForceAccumulationGui::newFrame() {
	PhysicsGUIBase::newFrame();
	keyboardInput = getUserDirection() * 2.0f;

	forceManager.updateForces();

	one.update(dt());	one.clearForce();
	two.update(dt());	two.clearForce();
	thr.update(dt());	thr.clearForce();

	for (int i = 0; i < numOfPoints; i++)
	{
		allPoints[i].pointGraphic->pointSize = allPoints[i].point->mass;
		syncVector(allPoints[i].pointGraphic,allPoints[i].point->pos);
		syncVector(allPoints[i].velGraphic,allPoints[i].point->vel, allPoints[i].point->pos);
		syncVector(allPoints[i].magGraphic,allPoints[i].point->momentum, allPoints[i].point->pos);
	}
}