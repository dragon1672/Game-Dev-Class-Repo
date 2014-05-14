#include <Qt/qapplication.h>
#include "Lab01VA\BasicVelocityAndAcc.h"
#include "Lab02FMA\BasicMomentum.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	//BasicVelocityAndAcc widg;
	BasicMomentum widg;

	widg.init();
	widg.show();
	return app.exec();
}