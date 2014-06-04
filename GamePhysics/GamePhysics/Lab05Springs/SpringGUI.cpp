#include "SpringGUI.h"

void SpringGUI::init() {
	mouseDragTimer.start();
	PhysicsGUIBase::init();
	myGrav.dir = glm::vec3();
	mySprings.init(12,4);
	myDrag.init(1,1);

	dragConst = 1;
	numOfParticles = 0;

	myDebugMenu.slideFloat("Gravity", myGrav.dir.y,0,-50);
	myDebugMenu.slideFloat("K", mySprings.springConstent,0,50);
	//myDebugMenu.slideFloat("Stiff K", mySprings.springConstent,0,500);
	myDebugMenu.slideFloat("Rest", mySprings.springRestLength,0,10);
	myDebugMenu.slideFloat("Rest", mySprings.springRestLength,0,100);
	myDebugMenu.slideFloat("dragConst", dragConst,0,10);
	myDebugMenu.button("single Chain", fastdelegate::MakeDelegate(this, &SpringGUI::toggleChangFun));
	myDebugMenu.button("double Chain", fastdelegate::MakeDelegate(this, &SpringGUI::toggleChangDoubleFun));
	myDebugMenu.button("complex Chain",fastdelegate::MakeDelegate(this, &SpringGUI::toggleComplexFun));

	numOfPoints = 0;
	numOfSpringRays = 0;
	numOfParticles++;
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3( 0,   0, 0);
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3(-2, 3.5, 0);
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3( 2, 3.5, 0);
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3( -.001,   7, 0);
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3(  .001,  11, 0);
	allPoints[numOfPoints++].point = &particalMem[numOfParticles++];	particalMem[numOfParticles-1].pos = glm::vec3(  .002,  12, 0);
		
	for (int i = 0; i < numOfPoints; i++)
	{
		allPoints[i].point->init(1);
		allPoints[i].pointGraphic = addVectorGraphic();
			allPoints[i].pointGraphic->color = glm::vec3(.5,.5,.5);
		allPoints[i].velGraphic   = addVectorGraphic();
			allPoints[i].velGraphic->displayStyle = DS_ARROW;
			allPoints[i].velGraphic->color = glm::vec3(1,0,0);
		forceManager.add(allPoints[i].point,&myGrav);
		forceManager.add(allPoints[i].point,&mySprings);
		forceManager.add(allPoints[i].point,&myDrag);
	}

	forceManager.remove(&particalMem[1],&myGrav);
	allPoints[0].pointGraphic->color = glm::vec3(.5,0,1); // setting anchor color

	toggleChain = toggleChain_last = toggleDoubleChain = toggleDoubleChain_last = toggleSep = toggleSep_last = toggleFull = toggleFull_last = false;

	mySprings.addSpring(particalMem[2],particalMem[1].pos); { springRayStruct temp = {&particalMem[2].pos, &particalMem[1].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start setting up to anchor
	mySprings.addSpring(particalMem[3],particalMem[1].pos); { springRayStruct temp = {&particalMem[3].pos, &particalMem[1].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // end   setting up to anchor
	mySprings.addSpring(particalMem[2],particalMem[3].pos); { springRayStruct temp = {&particalMem[2].pos, &particalMem[3].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start double joints
	mySprings.addSpring(particalMem[3],particalMem[2].pos); { springRayStruct temp = {&particalMem[3].pos, &particalMem[2].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[2],particalMem[4].pos); { springRayStruct temp = {&particalMem[2].pos, &particalMem[4].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[4],particalMem[2].pos); { springRayStruct temp = {&particalMem[4].pos, &particalMem[2].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[3],particalMem[4].pos); { springRayStruct temp = {&particalMem[3].pos, &particalMem[4].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[4],particalMem[3].pos); { springRayStruct temp = {&particalMem[4].pos, &particalMem[3].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[4],particalMem[5].pos); { springRayStruct temp = {&particalMem[4].pos, &particalMem[5].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[5],particalMem[4].pos); { springRayStruct temp = {&particalMem[5].pos, &particalMem[4].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[6],particalMem[5].pos); { springRayStruct temp = {&particalMem[6].pos, &particalMem[5].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[5],particalMem[6].pos); { springRayStruct temp = {&particalMem[5].pos, &particalMem[6].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[3],particalMem[6].pos); { springRayStruct temp = {&particalMem[3].pos, &particalMem[6].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[6],particalMem[3].pos); { springRayStruct temp = {&particalMem[6].pos, &particalMem[3].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[2],particalMem[5].pos); { springRayStruct temp = {&particalMem[2].pos, &particalMem[5].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[5],particalMem[2].pos); { springRayStruct temp = {&particalMem[5].pos, &particalMem[2].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[6],particalMem[4].pos); { springRayStruct temp = {&particalMem[6].pos, &particalMem[4].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[4],particalMem[6].pos); { springRayStruct temp = {&particalMem[4].pos, &particalMem[6].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	mySprings.addSpring(particalMem[4],particalMem[1].pos); { springRayStruct temp = {&particalMem[4].pos, &particalMem[1].pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
	for (int i = 0; i < numOfSpringRays; i++)
	{
		springRays[i].graphic->color = glm::vec3(1,.5,0);
		springRays[i].graphic->displayStyle = DS_ARROW;
	}
};
void SpringGUI::newFrame() {
	PhysicsGUIBase::newFrame();
		
	myDrag.high = myDrag.low = dragConst;

	if(mouseDragTimer.stop() > dt()*10) {
		updateForces();
		forceManager.updateForces();


		for (int i = 0; i < numOfPoints; i++)
		{
			allPoints[i].point->update(dt());
			allPoints[i].point->clearForce();
			allPoints[i].pointGraphic->pointSize = allPoints[i].point->mass;
			syncVector(allPoints[i].pointGraphic,allPoints[i].point->pos);
			syncVector(allPoints[i].velGraphic,allPoints[i].point->vel, allPoints[i].point->pos);
		}
		for (int i = 0; i < numOfSpringRays; i++)
		{
			glm::vec3 diff = *springRays[i].from - *springRays[i].to;
			syncVector(springRays[i].graphic,diff,*springRays[i].to);
		}
	}
}
void SpringGUI::toggleChangFun() {
	wipeSprings();
	mySprings.addSpring(particalMem[2],particalMem[1].pos); springRays[0].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[2].pos); springRays[3].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[3].pos); springRays[7].graphic  -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[4].pos); springRays[9].graphic  -> visible = true;
	mySprings.addSpring(particalMem[6],particalMem[5].pos); springRays[10].graphic -> visible = true;
}
void SpringGUI::toggleChangDoubleFun() {
	wipeSprings();
	mySprings.addSpring(particalMem[2],particalMem[1].pos); springRays[0].graphic  -> visible = true;
	mySprings.addSpring(particalMem[2],particalMem[3].pos); springRays[2].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[2].pos); springRays[3].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[4].pos); springRays[6].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[3].pos); springRays[7].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[5].pos); springRays[8].graphic  -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[4].pos); springRays[9].graphic  -> visible = true;
	mySprings.addSpring(particalMem[6],particalMem[5].pos); springRays[10].graphic -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[6].pos); springRays[11].graphic -> visible = true;
}
void SpringGUI::toggleComplexFun() {
	wipeSprings();
	mySprings.addSpring(particalMem[2],particalMem[1].pos); springRays[0].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[1].pos); springRays[1].graphic  -> visible = true;
	mySprings.addSpring(particalMem[2],particalMem[3].pos); springRays[2].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[2].pos); springRays[3].graphic  -> visible = true;
	mySprings.addSpring(particalMem[2],particalMem[4].pos); springRays[4].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[2].pos); springRays[5].graphic  -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[4].pos); springRays[6].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[3].pos); springRays[7].graphic  -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[5].pos); springRays[8].graphic  -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[4].pos); springRays[9].graphic  -> visible = true;
	mySprings.addSpring(particalMem[6],particalMem[5].pos); springRays[10].graphic -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[6].pos); springRays[11].graphic -> visible = true;
	mySprings.addSpring(particalMem[3],particalMem[6].pos); springRays[12].graphic -> visible = true;
	mySprings.addSpring(particalMem[6],particalMem[3].pos); springRays[13].graphic -> visible = true;
	mySprings.addSpring(particalMem[2],particalMem[5].pos); springRays[14].graphic -> visible = true;
	mySprings.addSpring(particalMem[5],particalMem[2].pos); springRays[15].graphic -> visible = true;
	mySprings.addSpring(particalMem[6],particalMem[4].pos); springRays[16].graphic -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[6].pos); springRays[17].graphic -> visible = true;
	mySprings.addSpring(particalMem[4],particalMem[1].pos); springRays[18].graphic -> visible = true;
}
void SpringGUI::updateForces() {
	if(toggleChain != toggleChain_last){
		toggleChangFun();
	}
	if(toggleDoubleChain != toggleDoubleChain_last) {
		toggleChangDoubleFun();
	}
	if(toggleFull!=toggleFull_last) {
		toggleComplexFun();
	}
	toggleChain_last = toggleChain;
	toggleDoubleChain_last = toggleDoubleChain;
	toggleFull_last = toggleFull;
}
void SpringGUI::wipeSprings() {
	mySprings.removeSpring(particalMem[2],particalMem[1].pos); springRays[0].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[3],particalMem[1].pos); springRays[1].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[2],particalMem[3].pos); springRays[2].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[3],particalMem[2].pos); springRays[3].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[2],particalMem[4].pos); springRays[4].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[4],particalMem[2].pos); springRays[5].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[3],particalMem[4].pos); springRays[6].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[4],particalMem[3].pos); springRays[7].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[4],particalMem[5].pos); springRays[8].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[5],particalMem[4].pos); springRays[9].graphic  -> visible = false;
	mySprings.removeSpring(particalMem[6],particalMem[5].pos); springRays[10].graphic -> visible = false;
	mySprings.removeSpring(particalMem[5],particalMem[6].pos); springRays[11].graphic -> visible = false;
	mySprings.removeSpring(particalMem[3],particalMem[6].pos); springRays[12].graphic -> visible = false;
	mySprings.removeSpring(particalMem[6],particalMem[3].pos); springRays[13].graphic -> visible = false;
	mySprings.removeSpring(particalMem[2],particalMem[5].pos); springRays[14].graphic -> visible = false;
	mySprings.removeSpring(particalMem[5],particalMem[2].pos); springRays[15].graphic -> visible = false;
	mySprings.removeSpring(particalMem[6],particalMem[4].pos); springRays[16].graphic -> visible = false;
	mySprings.removeSpring(particalMem[4],particalMem[6].pos); springRays[17].graphic -> visible = false;
	mySprings.removeSpring(particalMem[4],particalMem[1].pos); springRays[18].graphic -> visible = false;
}
void SpringGUI::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	mouseDragTimer.start();
	int index = vectorGraphicIndex / 2; // 2 graphics made for each point
	allPoints[index].point->pos += dragDelta;

	for (int i = 0; i < numOfPoints; i++)
	{
		syncVector(allPoints[i].pointGraphic,allPoints[i].point->pos);
		syncVector(allPoints[i].velGraphic,allPoints[i].point->vel, allPoints[i].point->pos);
	}
	for (int i = 0; i < numOfSpringRays; i++)
	{
		glm::vec3 diff = *springRays[i].from - *springRays[i].to;
		syncVector(springRays[i].graphic,diff,*springRays[i].to);
	}
}