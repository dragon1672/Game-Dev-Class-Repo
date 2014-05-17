#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <VectorBoundForceGenerator.h>

class SpringGUI : public PhysicsGUIBase {
	GravityForceGenerator myGrav;
	SpringForceGenerator mySprings;
	DragForceGenerator myDrag;

	ParticleForceRegistry forceManager;

	Particle one;
	Particle two;
	Particle thr;
	Particle fur;
	Particle fiv;
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
		PhysicsGUIBase::init();
		myGrav.dir = glm::vec3();
		mySprings.init(12,4);
		myDrag.init(1,1);
		myDebugMenu.slideFloat("Gravity", myGrav.dir.y,0,-50);
		myDebugMenu.slideFloat("K", mySprings.springConstent,0,50);
		myDebugMenu.slideFloat("Stiff K", mySprings.springConstent,0,500);
		myDebugMenu.slideFloat("Rest", mySprings.springRestLength,0,10);

		numOfPoints = 0;
		numOfSpringRays = 0;

		allPoints[numOfPoints++].point = &one;	one.pos = glm::vec3( 0,   0, 0);
		allPoints[numOfPoints++].point = &two;	two.pos = glm::vec3(-2, 3.5, 0);
		allPoints[numOfPoints++].point = &thr;	thr.pos = glm::vec3( 2, 3.5, 0);
		allPoints[numOfPoints++].point = &fur;	fur.pos = glm::vec3( 0,   7, 0);
		allPoints[numOfPoints++].point = &fiv;	fiv.pos = glm::vec3( 0,  11, 0);
		
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


		mySprings.addSpring(two,one.pos); { springRayStruct temp = {&two.pos, &one.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start setting up to anchor
		mySprings.addSpring(thr,one.pos); { springRayStruct temp = {&thr.pos, &one.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // end   setting up to anchor
		mySprings.addSpring(two,thr.pos); { springRayStruct temp = {&two.pos, &thr.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // start double joints
		mySprings.addSpring(thr,two.pos); { springRayStruct temp = {&thr.pos, &two.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(two,fur.pos); { springRayStruct temp = {&two.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fur,two.pos); { springRayStruct temp = {&fur.pos, &two.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(thr,fur.pos); { springRayStruct temp = {&thr.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fur,thr.pos); { springRayStruct temp = {&fur.pos, &thr.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; }
		mySprings.addSpring(fur,fiv.pos); { springRayStruct temp = {&fur.pos, &fiv.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } 
		mySprings.addSpring(fiv,fur.pos); { springRayStruct temp = {&fiv.pos, &fur.pos, addVectorGraphic()}; springRays[numOfSpringRays++] = temp; } // end double joints 
		for (int i = 0; i < numOfSpringRays; i++)
		{
			springRays[i].graphic->color = glm::vec3(1,.5,0);
			springRays[i].graphic->displayStyle = DS_ARROW;
		}
	};
	void newFrame() {
		PhysicsGUIBase::newFrame();

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
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
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