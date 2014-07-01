#include <Qt/qapplication.h>
#include "LabOne.h"
#include <Engine\BasicGui.h>


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	LabOne widg;

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}