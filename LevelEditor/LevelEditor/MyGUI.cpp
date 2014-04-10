#include "MyGUI.h"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <qt/qdebug.h>
#include <Qt/QFileDialog.h>

void MyGUI::mouseMoveEvent(QMouseEvent* e) {
	meScene.mouseMoveEvent(e);
}
void MyGUI::keyPressEvent(QKeyEvent* e) {
	meScene.keyPressEvent(e);
}
void MyGUI::loadObj() {
	QString targetObj = QFileDialog::getOpenFileName(this, "Open OBJ", "../Levels", "Object Files (*.obj)");
	if(targetObj == "")
		return;
	
	QString command("CSharpOBJConverter.exe ");
	const char* nativeFileName = "level.bin";
	command += "\""+targetObj + "\"" + " " + "\"" + nativeFileName+ "\"";
	int result = system(command.toUtf8().constData());
	if(result!=0) {
		qDebug() << "File failed to load";
		assert(false);
		return;
	}
	meScene.loadGeo("level.bin");
}
void MyGUI::saveNative() {

}
void MyGUI::saveNativeAs() {

}