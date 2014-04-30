#include "MyGUI.h"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <qt/qdebug.h>
#include <Qt/QFileDialog.h>
#include "LevelSerializer.h"

void MyGUI::mouseMoveEvent(QMouseEvent* e) {
	meScene.mouseMoveEvent(e);
}
void MyGUI::keyPressEvent(QKeyEvent* e) {
	meScene.keyPressEvent(e);
}
void MyGUI::myUpdate() {
	toggleDebugMenu.update(.1f);
	if(toggleDebugMenu.hasBeenClicked()) {
		if(myDebugMenu->isHidden()) myDebugMenu->show();
		else myDebugMenu->hide();
	}
	if(!myDebugMenu->isHidden()) {
		myDebugMenu->update();
	}
}