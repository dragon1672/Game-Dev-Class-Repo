#pragma once

#include "../PhysicsGUIBase.h"
#include <CollisionManager.h>
#include <Timer.h>
#include <GravityForceGenerator.h>
#include <ParticleForceRegistry.h>
#include <Ray.h>
#include <MyRandom.h>

class RestingContactGUI : public PhysicsGUIBase {
	Timer mouseDragTimer;

	static const int MAX_TOTAL_POINTS = 100;
	static const int STARTING_NUM_OF_POINTS = 10;

	Particle movingPoint;
	VectorGraphic * movingPointGraphic;

	struct {
		Particle point;
		VectorGraphic * pointGraphic;
		VectorGraphic * velGraphic;
	} allPoints[MAX_TOTAL_POINTS];
	int numOfPoints;

	Ray wall;
	VectorGraphic * wallGraphicLeft;
	VectorGraphic * wallGraphicRight;

	CollisionManager collisionManager;
	ParticleForceRegistry forceReg;
	GravityForceGenerator gravity;
public:
	void init() {
		PhysicsGUIBase::init();
		mouseDragTimer.start();

		numOfPoints = STARTING_NUM_OF_POINTS;
		
		for (int i = 0; i < MAX_TOTAL_POINTS; i++)
		{
			allPoints[i].point.pos = glm::vec3(-100,-100,-100);

			allPoints[i].point.init(1,1);
			allPoints[i].pointGraphic = addVectorGraphic();
			allPoints[i].velGraphic = addVectorGraphic();
			allPoints[i].velGraphic->displayStyle = DS_ARROW;
			allPoints[i].velGraphic->color = glm::vec3();

			sync(allPoints[i].pointGraphic,allPoints[i].point.pos);
			syncVector(allPoints[i].velGraphic,allPoints[i].point.vel,allPoints[i].point.pos);
		}

		movingPoint.init(1,1);
		movingPointGraphic = addVectorGraphic();

		collisionManager.walls.push_back(&wall);

		gravity.dir = glm::vec3(0,-9.81,0);
		wall.origin = glm::vec3();
		wall.direction =  glm::vec3(0,1,0);
		collisionManager.restitution = 0;

		wallGraphicLeft= addVectorGraphic();
		wallGraphicLeft->displayStyle = DS_ARROW;
		wallGraphicLeft->color = glm::vec3(0,1,0);
		wallGraphicRight= addVectorGraphic();
		wallGraphicRight->displayStyle = DS_ARROW;
		wallGraphicRight->color = glm::vec3(0,1,0);

		reset();

		myDebugMenu.button("Reset", fastdelegate::MakeDelegate(this,&RestingContactGUI::reset));
		myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,0,0,false);
		myDebugMenu.watch("Plane Norm",wall.direction);
		myDebugMenu.edit("Gravity",gravity.dir.y, 0, -10);
		myDebugMenu.edit("Restitution", collisionManager.restitution, 0, 1);
	};
	void reset() {
		movingPoint.pos = glm::vec3(-3,2.5,0);
		//movingPoint.vel = glm::vec3(.5f,0,.1);
		collisionManager.particles.clear();
		forceReg.clear();
		for (int i = 0; i < numOfPoints; i++)
		{
			allPoints[i].point.pos = glm::vec3(0,1,0) + (float)i * glm::vec3(0,1.5,0);
			allPoints[i].pointGraphic->color = Random::glmRand::randomUnitVector();
			allPoints[i].point.vel = glm::vec3(0,0,0);
			allPoints[i].velGraphic->color = glm::vec3(0,1,0);
			forceReg.add(allPoints[i].point,gravity);
			collisionManager.particles.push_back(&allPoints[i].point);
		}
		collisionManager.particles.push_back(&movingPoint);
	}
	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		wall.direction = glm::normalize(wall.direction);

		if(mouseDragTimer.stop() > dt()*10) {
			forceReg.updateForces();
			movingPoint.update(dt());
			for (int i = 0; i < numOfPoints; i++)
			{
				allPoints[i].point.update(dt());
			}

			collisionManager.makeItWork(dt());


			for (int i = 0; i < numOfPoints; i++)
			{
				allPoints[i].point.clearForce();
			}
		}

		redraw();
	}
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
		mouseDragTimer.start();
		if(vectorGraphicIndex >= MAX_TOTAL_POINTS * 2)
			movingPoint.pos += dragDelta;
		else
			allPoints[vectorGraphicIndex/2].point.pos += dragDelta;

		redraw();
	}
	void redraw() {
		for (int i = 0; i < numOfPoints; i++)
		{
			allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
			sync(allPoints[i].pointGraphic,allPoints[i].point.pos);
			syncVector(allPoints[i].velGraphic,allPoints[i].point.vel,allPoints[i].point.pos);
		}
		sync(movingPointGraphic,movingPoint.pos);
		glm::vec3 perpCCW = 1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
		glm::vec3 perpCW = -1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
		syncVector(wallGraphicLeft, perpCCW, wall.origin);
		syncVector(wallGraphicRight, perpCW, wall.origin);
	}
};


/* lab requirements
	1-	Particles falls down on top of each other to the ground.
	2-	Apply gravity.
	3-	Particles stand on top of each other making a pillar.
	4-	Particle come in from left and knocks the tower down.
	5-	Tower falls down in a realistic manner.
	6-	Reasonable UI controls (don’t make me stand on my head).
//*/