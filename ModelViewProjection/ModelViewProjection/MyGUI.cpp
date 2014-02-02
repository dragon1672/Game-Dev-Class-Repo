#include "MyGUI.h"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <qt/qdebug.h>

void MyGUI::mouseMoveEvent(QMouseEvent* e) {
	meScene.mouseMoveEvent(e);
}
void MyGUI::keyPressEvent(QKeyEvent* e) {
	meScene.keyPressEvent(e);
}
void MyGUI::updateFromScene() {
	//qDebug() << "updating from scene stuff";
	overrideColorEnabled(meScene.enableOverrideColor);
	showLightSource(meScene.displayLightEntity);
	setOverrideColor(meScene.overrideColor);
	setAmbCol(meScene.ambientLight);
	setDiffCol(meScene.diffuseLight);
	setDiffPos(meScene.diffusePos);
	inFragmentShaderLighting(meScene.diffuseInFrag);
}
void MyGUI::updateScene() {
	//qDebug() << "updating scene";
	meScene.enableOverrideColor = overrideColorEnabled();
	meScene.displayLightEntity = showLightSource();
	meScene.overrideColor = getOverrideColor();
	meScene.ambientLight = getAmbCol();
	meScene.diffuseLight = getDiffCol();
	meScene.diffusePos = getDiffPos();
	meScene.diffuseInFrag = inFragmentShaderLighting();
}

glm::vec3 MyGUI::getOverrideColor() {
	float r = overrideColor_R.value();
	float g = overrideColor_G.value();
	float b = overrideColor_B.value();
	return glm::vec3(r,g,b);
}
glm::vec3 MyGUI::getDiffPos() {
	float x = diffPos_X.value();
	float y = diffPos_Y.value();
	float z = diffPos_Z.value();
	return glm::vec3(x,y,z);
}
glm::vec3 MyGUI::getDiffCol() {
	float r = diffCol_R.value();
	float g = diffCol_G.value();
	float b = diffCol_B.value();
	return glm::vec3(r,g,b);
}
glm::vec3 MyGUI::getAmbCol() {
	float r = ambCol_R.value();
	float g = ambCol_G.value();
	float b = ambCol_B.value();
	return glm::vec3(r,g,b);
}

bool MyGUI::overrideColorEnabled() {
	return overrideColorEnabled_checkBox.isChecked();
}
bool MyGUI::inFragmentShaderLighting() {
	return inFragmentShaderLighting_checkBox.isChecked();
}
bool MyGUI::showLightSource() {
	return showLightSource_checkBox.isChecked();
}

void MyGUI::setOverrideColor(glm::vec3 toSet) {
	overrideColor_R.setValue(toSet.r);
	overrideColor_G.setValue(toSet.g);
	overrideColor_B.setValue(toSet.b);
}
void MyGUI::setDiffPos(glm::vec3 toSet) {
	diffPos_X.setValue(toSet.x);
	diffPos_Y.setValue(toSet.y);
	diffPos_Z.setValue(toSet.z);
}
void MyGUI::setDiffCol(glm::vec3 toSet) {
	diffCol_R.setValue(toSet.r);
	diffCol_G.setValue(toSet.g);
	diffCol_B.setValue(toSet.b);
}
void MyGUI::setAmbCol(glm::vec3 toSet) {
	ambCol_R.setValue(toSet.r);
	ambCol_G.setValue(toSet.g);
	ambCol_B.setValue(toSet.b);
}

void MyGUI::overrideColorEnabled(bool toSet) {
	overrideColorEnabled_checkBox.setChecked(toSet);
}
void MyGUI::inFragmentShaderLighting(bool toSet) {
	inFragmentShaderLighting_checkBox.setChecked(toSet);
}
void MyGUI::showLightSource(bool toSet) {
	showLightSource_checkBox.setChecked(toSet);
}
void MyGUI::myUpdate() {
	updateScene();
}