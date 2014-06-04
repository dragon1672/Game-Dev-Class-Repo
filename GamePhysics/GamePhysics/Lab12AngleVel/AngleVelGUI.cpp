#include "AngleVelGUI.h"


void AngleVelGUI::init() {
	PhysicsGUIBase::init();

	radius = 3;
	angleVel = .5;
	onChain = true;

	theWorld.init(&point,1,nullptr,0);
	point.init(1,.5);
	chainOrgin = glm::vec3(1,1,0);

	pointGraphic = addVectorGraphic();
	chainGraphic = addVectorGraphic();
	chainGraphic->displayStyle = DS_SQUARE;
	chainGraphic->color = glm::vec3(0,1,0);
	velGraphic = addVectorGraphic();
	velGraphic->displayStyle = DS_ARROW;
	radiusVector = addVectorGraphic();
	radiusVector->displayStyle = DS_ARROW;
	radiusVector->color = glm::vec3(.1,.1,.1);

	myDebugMenu.edit("On Chain: ",onChain);
	//myDebugMenu.edit("Chain\nPos",chainOrgin,-10,10);
	myDebugMenu.edit("Radius: ",radius,.0001,5);
	myDebugMenu.edit("Angle Vel: ",angleVel,0,10);
};
glm::vec3 AngleVelGUI::getRad() {
	glm::vec3 diff = point.pos - chainOrgin;
	glm::vec3 norm = glm::normalize(diff);
	glm::vec3 expanded = radius * norm;
	return radius * glm::normalize(point.pos - chainOrgin);
}
void AngleVelGUI::updateAnglur() {
	storedRadiusVector = getRad();

	if(onChain) {
		glm::vec3 rad = getRad();
		point.pos = chainOrgin + rad;
		glm::vec3 perp = glm::perp(rad,glm::vec3(0,0,1));
		perp = glm::vec3(-rad.y,rad.x,0);
		point.vel = perp * angleVel;
	}
}
void AngleVelGUI::newFrame() {
	PhysicsGUIBase::newFrame();
		
	theWorld.update(dt());

	updateAnglur();

	redraw();
}
void AngleVelGUI::vectorGraphicMouseDrag(uint vectorGraphicIndex, const glm::vec3& dragDelta) {
	if(vectorGraphicIndex == 1) {
		chainOrgin += glm::vec3(glm::vec2(dragDelta),0);
	}

	updateAnglur();

	redraw();
}
void AngleVelGUI::redraw() {
	pointGraphic->pointSize = point.mass;
	sync(pointGraphic,point.pos);
	sync(velGraphic,point.vel,point.pos);
	sync(chainGraphic,chainOrgin);
	sync(radiusVector, storedRadiusVector, chainOrgin);
}