#include <Qt/qapplication.h>
#include "Lab01VA\BasicVelocityAndAcc.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	BasicVelocityAndAcc widg;


	widg.init();
	widg.show();
	return app.exec();
}