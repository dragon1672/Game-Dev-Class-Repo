#pragma once

#include "../PhysicsGUIBase.h"
#include <GravityBodyForceGenerator.h>
#include <Particle.h>
#include <MyRandom.h>

class SomethingCool : public PhysicsGUIBase {
	GravityBodyForceGenerator myGrav;
	CollisionManager collisionManager;

	static const int NUM_OF_POINTS = 1000;

	float spawnForce;
	float range;

	struct {
		Particle point;
		VectorGraphic * pointGraphic;
	} points[NUM_OF_POINTS];

	void initGraphic(VectorGraphic** leGraphic, glm::vec3& col, DisplayStyle type = DS_ARROW) {
		(*leGraphic)  = addVectorGraphic();
		(*leGraphic) -> displayStyle = type;
		(*leGraphic) -> color = col;
	}
	static bool circleCollide(Particle * a, Particle * b) {
		glm::vec3 diff = a->pos - b->pos;
		float rads = a->mass/2 + b->mass/2;
		float lengthSquared = glm::dot(diff,diff);
		return lengthSquared < rads * rads;
	}
	bool collide(Particle * a, Particle * b, ParticleContact& outPram) {
		bool valid = circleCollide(a,b);
		if(valid) {
			glm::vec3 diff = a->pos - b->pos;
			float diffLength = glm::length(diff);
			glm::vec3 collisionNorm = diff / diffLength;
			float pen = (a->mass/2 + b->mass/2) - diffLength;

			outPram.particle[0] = a;
			outPram.particle[1] = b;
			outPram.contactNormal = collisionNorm;
			outPram.penetration = pen;
			outPram.restitution = 0;
		}
		return valid;
	}
public:
	void init() {
		PhysicsGUIBase::init(true,false);

		myGrav.init(4);

		spawnForce = 30;
		range = 10;

		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			points[i].point.init(50);
			initGraphic(&points[i].pointGraphic,glm::vec3(0,0,1),DisplayStyle::DS_POINT);
			myGrav.addBody(points[i].point);
		}

		reset();

		myDebugMenu.button("Reset",fastdelegate::MakeDelegate(this,&SomethingCool::reset));
		myDebugMenu.edit("Grav Const",myGrav.gravityConstent,0,50);
		myDebugMenu.edit("Spawn Force",spawnForce,0,100);
		myDebugMenu.edit("Spawn Range",range,0,100);
	}
	void reset() {
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			points[i].point.init(1);
			points[i].point.pos = Random::glmRand::randomFloatVectorInBoxRanged(range,range,range);
			points[i].point.vel = spawnForce * Random::glmRand::randomUnitVector();
			points[i].point.mass = Random::randomFloat(1, 2);
		}
		redraw();
	}

	void newFrame() {
		PhysicsGUIBase::newFrame();
		
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			myGrav.updateForce(&points[i].point);
			for (int j = i+1; j < NUM_OF_POINTS; j++)
			{
				ParticleContact temp;
				if(collide(&points[i].point, &points[j].point,temp)) {
					temp.resolve(dt());
				}
			}
			points[i].point.update(dt());
		}

		redraw();
	}
	void redraw() {
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			points[i].pointGraphic->pointSize = points[i].point.mass;
			sync(points[i].pointGraphic,points[i].point.pos);
		}
	}
};