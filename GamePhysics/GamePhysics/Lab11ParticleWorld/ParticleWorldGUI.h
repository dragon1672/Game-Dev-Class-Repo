#pragma once

#include "../PhysicsGUIBase.h"
#include <ParticleWorld.h>
#include <SpringForceGenerator.h>
#include <GravityForceGenerator.h>
#include <DragForceGenerator.h>

class ParticleWorldGUI : public PhysicsGUIBase {

	static const int SQUARE_LENGTH = 5;
	static const int tesselation = 6; // must be at least 2

	SpringForceGenerator springs;
	DragForceGenerator myDrag;
	ParticleWorld theWorld;

	static const int NUM_OF_POINTS = (tesselation) * (tesselation) * (tesselation);

	Particle points[NUM_OF_POINTS];
	VectorGraphic * pointGraphics[NUM_OF_POINTS];
	uint numOfPoints;

	Ray wall;

	float damp;
	float squareLength;

	GravityForceGenerator gravity;
	
public:
	void init();
	Particle * getParticle(glm::vec3& pos, float epsilon = .01);
	void reset();
	void newFrame();
	void vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta);
	void redraw();
};
