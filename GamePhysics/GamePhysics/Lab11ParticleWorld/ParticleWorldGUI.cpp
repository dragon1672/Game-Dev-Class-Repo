#include "ParticleWorldGUI.h"

void ParticleWorldGUI::init() {
	PhysicsGUIBase::init(true);

	squareLength = SQUARE_LENGTH;

	theWorld.init(points,NUM_OF_POINTS,&wall,1,0);
	myDrag.init(1,1);

	damp = .9f;

	gravity.dir = glm::vec3(0,-5,0);
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
	}

	myDebugMenu.button("Reset", fastdelegate::MakeDelegate(this,&ParticleWorldGUI::reset));
	myDebugMenu.edit("Spring K",springs.springConstent,0,75);
	myDebugMenu.edit("Square Length",squareLength,0,4);
	//myDebugMenu.edit("Plane Norm",wall.direction,-1,1,0,1,-1,1,false);
	myDebugMenu.edit("Gravity",gravity.dir.y, -10, 10);
	myDebugMenu.edit("Particle\nCollisions", theWorld.collisionManager.particleCollide);
	myDebugMenu.edit("Restitution", theWorld.getRestitution(), 0, 1);
	myDebugMenu.edit("Damp", damp, 0, 1);
	//myDebugMenu.edit("Drag Low", myDrag.low, 0, 1);
	//myDebugMenu.edit("Drag High", myDrag.high, 0, 1);
};
Particle * ParticleWorldGUI::getParticle(glm::vec3& pos, float epsilon) {
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		glm::vec3 diff = points[i].pos - pos;
		if(glm::dot(diff,diff) < epsilon) return &points[i];
	}
	return nullptr;
}
void ParticleWorldGUI::reset() {
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		points[i].vel = glm::vec3();
	}

	glm::vec3 offset = glm::vec3(0,squareLength+5,0);
	float length = squareLength*2 / (tesselation-1);
	numOfPoints = 0;
	for (float x = -squareLength; x <= squareLength; x+=length)
	{
		for (float y = -squareLength; y <= squareLength; y+=length)
		{
			for (float z = -squareLength; z <= squareLength; z+=length)
			{
				points[numOfPoints++].pos = glm::vec3(x,y,z) + offset;
			}
		}
	}
	springs.clear();
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		for (float x = -length; x <= length; x+=length)
		{
			for (float y = -length; y <= length; y+=length)
			{
				for (float z = -length; z <= length; z+=length)
				{
					glm::vec3 offset(x,y,z);
					if(glm::dot(offset,offset) != 0) {
						Particle * toLinkTo = getParticle(points[i].pos + offset);
						if(toLinkTo != nullptr) {
							float length = glm::length(points[i].pos - toLinkTo->pos);
							springs.addSpring(points[i],toLinkTo->pos,length);
						}
					}
				}
			}
		} 
	}
}
void ParticleWorldGUI::newFrame() {
	PhysicsGUIBase::newFrame();
		
	if(glm::dot(wall.direction,wall.direction) == 0) wall.direction = glm::vec3(0,.000000001,0);
	wall.direction = glm::normalize(wall.direction);
	for (int i = 0; i < NUM_OF_POINTS; i++) { points[i].drag = damp; }

	theWorld.update(dt());
	redraw();
}
void ParticleWorldGUI::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	points[vectorGraphicIndex].pos += dragDelta;
	redraw();
}
void ParticleWorldGUI::redraw() {
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pointGraphics[i]->pointSize = points[i].mass;
		sync(pointGraphics[i],points[i].pos);
	}
}