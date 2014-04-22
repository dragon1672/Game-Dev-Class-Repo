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
		return;
	} else {
		meScene.loadGeo("level.bin");
	}
}

void MyGUI::loadBin() {
	QString targetObj = QFileDialog::getOpenFileName(this, "Open Binary", "../Levels", "Object Files (*.bin)");
	if(targetObj == "")
		return;
	targetObj = targetObj.replace('/','\\');
	
	QString command("copy ");
	QString nativeFileName = "level.bin";
	command += "\""+ targetObj + "\"" + " " + "\"" + nativeFileName + "\"";
	qDebug() << command;
	int result = system(command.toUtf8().constData());
	if(result!=0) {
		qDebug() << "File failed to load";
		return;
	} else {
		meScene.loadGeo("level.bin");
	}
}

void MyGUI::loadLevel() {
	char * levelBinary = LevelSerializer::readFile("..\\output.lvl",meScene.myNodeManager);
	meScene.loadGeoFromBinary(levelBinary);
}
void MyGUI::saveNative() {
	LevelSerializer::writeFile("level.bin",meScene.myNodeManager,"..\\output.lvl");
}
void MyGUI::saveNativeAs() {

}