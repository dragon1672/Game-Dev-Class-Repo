#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>
#include <Timer.h>

class ParticleWorldGUI : public PhysicsGUIBase {
	Timer mouseDragTimer;
	SpringForceGenerator springs;
	DragForceGenerator myDrag;
	ParticleWorld theWorld;

	static const int NUM_OF_POINTS = 8;

	Particle points[NUM_OF_POINTS];
	VectorGraphic * pointGraphics[NUM_OF_POINTS];
	uint numOfPoints;

	Ray wall;

	float damp;

	GravityForceGenerator gravity;
	
public:
	void init() {
		PhysicsGUIBase::init(true);
		mouseDragTimer.start();

		theWorld.init(points,NUM_OF_POINTS,&wall,1,0);
		myDrag.init(1,1);

		damp = .9f;

		gravity.dir = glm::vec3(0,-9.81,0);
		wall.origin = glm::vec3();
		wall.direction =  glm::vec3(0,1,0);

		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			points[i].init(damp,1);
			pointGraphics[i] = addVectorGraphic();
		}

		reset();

		springs.init(25);

		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			theWorld.addForce(i,&springs);
			theWorld.addForce(i,&gravity);
			theWorld.addForce(i,&myDrag);
			for (int j = 0; j < NUM_OF_POINTS; j++)
			{
				if(i!=j) {
					float length = glm::length(points[i].pos - points[j].pos);
					springs.addSpring(points[i],points[j].pos, length);
				}
			}
		}

		myDebugMenu.button("Reset", fastdelegate::MakeDelegate(this,&ParticleWorldGUI::reset));
		myDebugMenu.edit("Spring K",springs.springConstent,0,100);
		myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,-1,1,false);
		myDebugMenu.edit("Gravity",gravity.dir, -10, 10);
		myDebugMenu.edit("Restitution", theWorld.getRestitution(), 0, 1);
		myDebugMenu.edit("Damp", damp, 0, 1);
		myDebugMenu.edit("Drag Low", myDrag.low, 0, 1);
		myDebugMenu.edit("Drag High", myDrag.high, 0, 1);
	};
	void reset() {
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			points[i].vel = glm::vec3();
		}
		points[0].pos = 2.0f * glm::vec3(-1, 0, 1) + glm::vec3(0,1,0);
		points[1].pos = 2.0f * glm::vec3(-1, 0,-1) + glm::vec3(0,1,0);
		points[2].pos = 2.0f * glm::vec3( 1, 0, 1) + glm::vec3(0,1,0);
		points[3].pos = 2.0f * glm::vec3( 1, 0,-1) + glm::vec3(0,1,0);
		points[4].pos = 2.0f * glm::vec3(-1, 2, 1) + glm::vec3(0,1,0);
		points[5].pos = 2.0f * glm::vec3(-1, 2,-1) + glm::vec3(0,1,0);
		points[6].pos = 2.0f * glm::vec3( 1, 2, 1) + glm::vec3(0,1,0);
		points[7].pos = 2.0f * glm::vec3( 1, 2,-1) + glm::vec3(0,1,0);
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		if(glm::dot(wall.direction,wall.direction) == 0) wall.direction = glm::vec3(0,.000000001,0);
		wall.direction = glm::normalize(wall.direction);
		for (int i = 0; i < NUM_OF_POINTS; i++) { points[i].drag = damp; }

		//if(mouseDragTimer.stop() > dt()*10) {
			theWorld.update(dt());
		//}
		redraw();
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		mouseDragTimer.start();
		points[vectorGraphicIndex].pos += dragDelta;
		redraw();
	}
	void redraw() {
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			pointGraphics[i]->pointSize = points[i].mass;
			sync(pointGraphics[i],points[i].pos);
		}
	}
};
