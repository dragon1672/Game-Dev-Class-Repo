#include <Qt/qapplication.h>
#include "LabOne.h"
#include "DebugMenuDemo.h"
#include <Engine\BasicGui.h>


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	//LabOne widg;
	DebugMenuDemo widg;

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}