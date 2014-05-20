#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleForceRegistry.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <Timer.h>

class WaveGui : public PhysicsGUIBase {
	SpringForceGenerator mySprings;
	DragForceGenerator myDrag;
	GravityForceGenerator myGrav;
	ParticleForceRegistry forceManager;

	float dragConst;
	float startingY;
	float endingY;
	float speed;
	float range;

	static const int NUM_OF_NODES = 50;

	struct {
		Particle point;
		VectorGraphic * pointGraphic;
	} allPoints[NUM_OF_NODES];
	int numOfNodes;

	struct springRayStruct {
		glm::vec3 * from;
		glm::vec3 * to;
		VectorGraphic * graphic;
	} springRays[NUM_OF_NODES];
public:
	void init() {
		PhysicsGUIBase::init();
		myGrav.dir = glm::vec3(0,10,0);
		mySprings.init(150,1);
		myDrag.init(1,1);

		dragConst = 0;
		numOfNodes = 0;
		speed = 30;
		range = 5;

		myDebugMenu.slideFloat("K", mySprings.springConstent,100,250);
		myDebugMenu.slideFloat("dragConst", dragConst,0,.25);
		myDebugMenu.slideFloat("Speed", speed,0,50);
		myDebugMenu.slideFloat("Range", range,0,10);


		for (int i = 0; i < NUM_OF_NODES; i++)
		{
			bool first = i==0;
			bool last  = i==NUM_OF_NODES-1; 
			allPoints[i].point.init(1,1);
			allPoints[i].point.pos = glm::vec3(0,0,0) + (float)i * glm::vec3(mySprings.springRestLength,0,0);
			if(first) startingY = allPoints[i].point.pos.x;
			if(last)  endingY   = allPoints[i].point.pos.x;

			allPoints[i].pointGraphic = addVectorGraphic();
				allPoints[i].pointGraphic->color = glm::vec3(.5,.5,.5);
			if(!first) {
				forceManager.add(allPoints[i].point,mySprings);
				forceManager.add(allPoints[i].point,myDrag);
			}

			if(!first) {
				mySprings.addSpring(allPoints[i].point,allPoints[i-1].point.pos);
				springRayStruct temp = {
					&allPoints[i-1].point.pos,
					&allPoints[i].point.pos,
					addVectorGraphic()
				};
				temp.graphic->color = glm::vec3(1,.5,0);
				temp.graphic->displayStyle = DS_ARROW;
				springRays[i-1] = temp;
			}
			if(!last) {
				mySprings.addSpring(allPoints[i].point,allPoints[i+1].point.pos);
			}
			numOfNodes++;
		}
		allPoints[0].pointGraphic->color = glm::vec3(.5,0,1); // setting anchor color
	};
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		myDrag.high = myDrag.low = dragConst;

		forceManager.updateForces();

		//updating start
		static float direction = 1;
		if(allPoints[0].point.pos.y >  range) direction = -1;
		if(allPoints[0].point.pos.y < -range) direction =  1;
		allPoints[0].point.vel = glm::vec3(0,direction * speed,0);
		allPoints[0].point.pos.x = startingY;
		//updating end
		allPoints[numOfNodes-1].point.pos.x = endingY;


		for (int i = 0; i < numOfNodes; i++)
		{
			float xBefore = allPoints[i].point.pos.x;
			allPoints[i].point.update(dt());
			allPoints[i].point.pos.x = xBefore;
			allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
			syncVector(allPoints[i].pointGraphic,allPoints[i].point.pos);
			//connection vectors
			if(i>0 && i < numOfNodes-1) {
				glm::vec3 diff = *springRays[i-1].from - *springRays[i-1].to;
				syncVector(springRays[i-1].graphic,diff,*springRays[i-1].to);
			}
		}
	}
};