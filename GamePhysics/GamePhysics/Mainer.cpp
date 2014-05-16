#include <Qt/qapplication.h>
#include "Lab01VA\BasicVelocityAndAcc.h"
#include "Lab02FMA\BasicMomentum.h"
#include "Lab03Force\ForceAccumulationGui.h"
#include "Lab04DragForce\DragForceGUI.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	//BasicVelocityAndAcc widg;
	//BasicMomentum widg;
	//ForceAccumulationGui widg;
	DragForceGUI widg;


	widg.init();
	widg.show();
	return app.exec();
}