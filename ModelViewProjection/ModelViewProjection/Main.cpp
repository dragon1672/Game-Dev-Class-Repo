#include <Qt/qapplication.h>
#include "MyWindow.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	MyWindow widg;
	 widg.show();
	 return app.exec();
}