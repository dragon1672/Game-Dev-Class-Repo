#include <Qt/qapplication.h>
#include "LabOne.h"
#include "DebugMenuDemo.h"
#include "AlphaBlending.h"
#include "NormalMaps.h"
#include "TangentSpace.h"
#include "Orge.h"
#include <Engine\BasicGui.h>


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	//LabOne widg;
	//DebugMenuDemo widg;
	//AlphaBlending widg;
	//NormalMaps widg;
	//TangentSpace widg;
	Orge widg;

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}