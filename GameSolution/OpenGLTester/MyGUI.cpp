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
	//nothing
}
void MyGUI::updateScene() {
	debugMenu->update();
}

void MyGUI::myUpdate() {
	toggleDebugMenu.update(.1f);
	if(toggleDebugMenu.hasBeenClicked()) {
		if(debugMenu->isHidden()) debugMenu->show();
		else debugMenu->hide();
	}
	if(!debugMenu->isHidden()) {
		updateScene();
	}
}