#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <VectorBoundForceGenerator.h>
#include <Timer.h>

class SpringGUI : public PhysicsGUIBase {
	GravityForceGenerator myGrav;
	SpringForceGenerator mySprings;
	DragForceGenerator myDrag;

	ParticleForceRegistry forceManager;

	Timer mouseDragTimer;

	bool toggleChain;
	bool toggleChain_last;
	bool toggleDoubleChain;
	bool toggleDoubleChain_last;
	bool toggleFull;
	bool toggleFull_last;
	bool pauseOnMouseClick;

	float dragConst;

	Particle one;
	Particle two;
	Particle thr;
	Particle fur;
	Particle fiv;
	Particle six;
	struct {
		Particle * point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
		VectorGraphic * magGraphic;
	} allPoints[10];
	int numOfPoints;
	struct springRayStruct {
		glm::vec3 * from;
		glm::vec3 * to;
		VectorGraphic * graphic;
	} springRays[20];
	int numOfSpringRays;
public:
	void init() {
		mouseDragTimer.start();
		PhysicsGUIBase::init();
		myGrav.dir = glm::vec3();
		mySprings.init(12,4);
		myDrag.init(1,1);

		dragConst = 1;

		pauseOnMouseClick = true;

		myDebugMenu.slideFloat("Gravity", myGrav.dir.y,0,-50);
		myDebugMenu.slideFloat("K", mySprings.springConstent,0,50);
		//myDebugMenu.slideFloat("Stiff K", mySprings.springConstent,0,500);
		myDebugMenu.slideFloat("Rest", mySprings.springRestLength,0,10);
		myDebugMenu.slideFloat("Rest", mySprings.springRestLength,0,100);
		myDebugMenu.slideFloat("dragConst", dragConst,0,10);
		myDebugMenu.toggleBool("[button] single Chain",toggleChain);
		myDebugMenu.toggleBool("[button] double Chain",toggleDoubleChain);
		myDebugMenu.toggleBool("[button] complex Chain",toggleFull);
		myDebugMenu.toggleBool("Pause on Mouse Drag",pauseOnMouseClick);

		numOfPoints = 0;
		numOfSpringRays = 0;

		allPoints[numOfPoints++].point = &one;	one.pos = glm::vec3( 0,   0, 0);
		allPoints[numOfPoints++].point = &two;	two.pos = glm::vec3(-2, 3.5, 0);
		allPoints[numOfPoints++].point = &thr;	thr.pos = glm::vec3( 2, 3.5, 0);
		allPoints[numOfPoints++].point = &fur;	fur.pos = glm::vec3( -.001,   7, 0);
		allPoints[numOfPoints++].point = &fiv;	fiv.pos = glm::vec3(  .001,  11, 0);
		allPoints[numOfPoints++].point = &six;	six.pos = glm::vec3(  .002,  12, 0);
		
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

		forceManager.remove(&one,&myGrav);
		allPoints[0].pointGraphic->color = glm::vec3(.5,0,1); // setting anchor color


		toggleChain = toggleChain_last = toggleDoubleChain = toggleChain_last = false;
		toggleFull = toggleFull_last = true;

		mySprings.addSpring(two,one.pos); { springRayStruct temp = {&two.pos, &one.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start setting up to anchor
		mySprings.addSpring(thr,one.pos); { springRayStruct temp = {&thr.pos, &one.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // end   setting up to anchor
		mySprings.addSpring(two,thr.pos); { springRayStruct temp = {&two.pos, &thr.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start double joints
		mySprings.addSpring(thr,two.pos); { springRayStruct temp = {&thr.pos, &two.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(two,fur.pos); { springRayStruct temp = {&two.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fur,two.pos); { springRayStruct temp = {&fur.pos, &two.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(thr,fur.pos); { springRayStruct temp = {&thr.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fur,thr.pos); { springRayStruct temp = {&fur.pos, &thr.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
		mySprings.addSpring(fur,fiv.pos); { springRayStruct temp = {&fur.pos, &fiv.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fiv,fur.pos); { springRayStruct temp = {&fiv.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
		mySprings.addSpring(fiv,fur.pos); { springRayStruct temp = {&six.pos, &fiv.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
		mySprings.addSpring(fiv,fur.pos); { springRayStruct temp = {&fiv.pos, &six.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // end double joints 
		for (int i = 0; i < numOfSpringRays; i++)
		{
			springRays[i].graphic->color = glm::vec3(1,.5,0);
			springRays[i].graphic->displayStyle = DS_ARROW;
		}
	};
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		myDrag.high = myDrag.low = dragConst;

		if(mouseDragTimer.stop() > dt()*10 || !pauseOnMouseClick) {
			updateForces();
			forceManager.updateForces();


			for (int i = 0; i < numOfPoints; i++)
			{
				allPoints[i].point->update(dt());
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
	void updateForces() {
		if(toggleChain != toggleChain_last){
			wipeSprings();
			mySprings.addSpring(two,one.pos); springRays[0].graphic->visible = true;
			mySprings.addSpring(thr,two.pos); springRays[3].graphic->visible = true;
			mySprings.addSpring(fur,thr.pos); springRays[7].graphic->visible = true;
			mySprings.addSpring(fiv,fur.pos); springRays[9].graphic->visible = true;
			mySprings.addSpring(six,fiv.pos); springRays[10].graphic->visible = true;
		}
		if(toggleDoubleChain != toggleDoubleChain_last) {
			wipeSprings();
			mySprings.addSpring(two,one.pos); springRays[0].graphic->visible = true;
			mySprings.addSpring(two,thr.pos); springRays[2].graphic->visible = true;
			mySprings.addSpring(thr,two.pos); springRays[3].graphic->visible = true;
			mySprings.addSpring(thr,fur.pos); springRays[6].graphic->visible = true;
			mySprings.addSpring(fur,thr.pos); springRays[7].graphic->visible = true;
			mySprings.addSpring(fur,fiv.pos); springRays[8].graphic->visible = true;
			mySprings.addSpring(fiv,fur.pos); springRays[9].graphic->visible = true;
			mySprings.addSpring(six,fiv.pos); springRays[10].graphic->visible = true;
			mySprings.addSpring(fiv,six.pos); springRays[11].graphic->visible = true;
		}
		if(toggleFull!=toggleFull_last) {
			wipeSprings();
			mySprings.addSpring(two,one.pos); springRays[0].graphic->visible = true;
			mySprings.addSpring(thr,one.pos); springRays[1].graphic->visible = true;
			mySprings.addSpring(two,thr.pos); springRays[2].graphic->visible = true;
			mySprings.addSpring(thr,two.pos); springRays[3].graphic->visible = true;
			mySprings.addSpring(two,fur.pos); springRays[4].graphic->visible = true;
			mySprings.addSpring(fur,two.pos); springRays[5].graphic->visible = true;
			mySprings.addSpring(thr,fur.pos); springRays[6].graphic->visible = true;
			mySprings.addSpring(fur,thr.pos); springRays[7].graphic->visible = true;
			mySprings.addSpring(fur,fiv.pos); springRays[8].graphic->visible = true;
			mySprings.addSpring(fiv,fur.pos); springRays[9].graphic->visible = true;
			mySprings.addSpring(six,fiv.pos); springRays[10].graphic->visible = true;
			mySprings.addSpring(fiv,six.pos); springRays[11].graphic->visible = true;
		}
		toggleChain_last = toggleChain;
		toggleDoubleChain_last = toggleDoubleChain;
		toggleFull_last = toggleFull;
	}
	void wipeSprings() {
		mySprings.removeSpring(two,one.pos); springRays[0].graphic->visible = false;
		mySprings.removeSpring(thr,one.pos); springRays[1].graphic->visible = false;
		mySprings.removeSpring(two,thr.pos); springRays[2].graphic->visible = false;
		mySprings.removeSpring(thr,two.pos); springRays[3].graphic->visible = false;
		mySprings.removeSpring(two,fur.pos); springRays[4].graphic->visible = false;
		mySprings.removeSpring(fur,two.pos); springRays[5].graphic->visible = false;
		mySprings.removeSpring(thr,fur.pos); springRays[6].graphic->visible = false;
		mySprings.removeSpring(fur,thr.pos); springRays[7].graphic->visible = false;
		mySprings.removeSpring(fur,fiv.pos); springRays[8].graphic->visible = false;
		mySprings.removeSpring(fiv,fur.pos); springRays[9].graphic->visible = false;
		mySprings.removeSpring(six,fiv.pos); springRays[10].graphic->visible = false;
		mySprings.removeSpring(fiv,six.pos); springRays[11].graphic->visible = false;
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
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
};