#include "RestingContactGUI.h"

void RestingContactGUI::init() {
	PhysicsGUIBase::init();
	mouseDragTimer.start();

	numOfPoints = STARTING_NUM_OF_POINTS + 1;
	resetNumOfParticles = numOfPoints-1;
		
	for (int i = 0; i < MAX_TOTAL_POINTS; i++)
	{
		allPoints[i].point.pos = glm::vec3(-100,-100,-100);

		allPoints[i].point.init(1,1);
		allPoints[i].pointGraphic = addVectorGraphic();
		allPoints[i].velGraphic = addVectorGraphic();
		allPoints[i].velGraphic->displayStyle = DS_ARROW;
		allPoints[i].velGraphic->color = glm::vec3();

		sync(allPoints[i].pointGraphic,allPoints[i].point.pos);
		//syncVector(allPoints[i].velGraphic,allPoints[i].point.vel,allPoints[i].point.pos);
	}

	//collisionManager.walls.push_back(&wall);

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

	sideMovingStart = glm::vec3(1,.26,.026);

	reset();

	myDebugMenu.button("Reset", fastdelegate::MakeDelegate(this,&RestingContactGUI::reset));
	myDebugMenu.edit("# Nodes", resetNumOfParticles, 1,50);
	myDebugMenu.edit("Starting Vel:",sideMovingStart,0,1,-1,1,-.1,.1);
	myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,1,1,false);
	myDebugMenu.edit("Gravity",gravity.dir.y, 0, -10);
	myDebugMenu.edit("Restitution", collisionManager.restitution, 0, 1);
};
void RestingContactGUI::reset() {
	numOfPoints = (int)resetNumOfParticles + 1;
	for (int i = 0; i < MAX_TOTAL_POINTS; i++)
	{
		allPoints[i].point.pos = glm::vec3(-100,-100,-100);
		sync(allPoints[i].pointGraphic,allPoints[i].point.pos);
		syncVector(allPoints[i].velGraphic,allPoints[i].point.vel,allPoints[i].point.pos);
	}
	//collisionManager.particles.clear();
	forceReg.clear();
	for (int i = 0; i < numOfPoints; i++)
	{
		if(i==0) {
			allPoints[i].point.pos = glm::vec3(-3,3,0);
			allPoints[i].point.vel = sideMovingStart;
		} else {
			allPoints[i].point.pos = glm::vec3(0,1,0) + (float)i * glm::vec3(0,1.5,0);
			allPoints[i].point.vel = glm::vec3(0,0,0);
			forceReg.add(allPoints[i].point,gravity);
		}
		allPoints[i].pointGraphic->color = Random::glmRand::randomUnitVector();
		allPoints[i].velGraphic->color = glm::vec3(0,1,0);
		//collisionManager.particles.push_back(&allPoints[i].point);
	}
}
void RestingContactGUI::newFrame() {
	PhysicsGUIBase::newFrame();
		
	wall.direction = glm::normalize(wall.direction);

	if(mouseDragTimer.stop() > dt()*10) {
		forceReg.updateForces();

		for (int i = 0; i < numOfPoints; i++)
		{
			allPoints[i].point.update(dt());
			ParticleContact wallCollision;
			if(collisionManager.collide(&allPoints[i].point,&wall, wallCollision)) {
				wallCollision.collide(dt());
			}
			for (int j = 0; j < numOfPoints; j++)
			{
				if(i!=j) {
					ParticleContact particleCollision;
					if(collisionManager.collide(&allPoints[i].point,&allPoints[j].point, particleCollision)) {
						particleCollision.collide(dt());
					}
				}
			}
		}
	}
	redraw();
}
void RestingContactGUI::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	mouseDragTimer.start();
	allPoints[vectorGraphicIndex/2].point.pos += dragDelta;
	redraw();
}
void RestingContactGUI::redraw() {
	for (int i = 0; i < numOfPoints; i++)
	{
		allPoints[i].pointGraphic->pointSize = allPoints[i].point.mass;
		sync(allPoints[i].pointGraphic,allPoints[i].point.pos);
		//syncVector(allPoints[i].velGraphic,allPoints[i].point.vel,allPoints[i].point.pos);
	}
	glm::vec3 perpCCW = 1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
	glm::vec3 perpCW = -1000.0f * glm::vec3(wall.direction.y,-wall.direction.x,0);
	//syncVector(wallGraphicLeft, perpCCW, wall.origin);
	//syncVector(wallGraphicRight, perpCW, wall.origin);
}