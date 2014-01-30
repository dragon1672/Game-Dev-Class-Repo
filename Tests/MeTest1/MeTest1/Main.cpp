#include <Qt/qwidget.h>
#include <Qt/qapplication.h>
#include "MyWindow.h"

int main(int argc, char*argv[]) {
	QApplication(argc,argv);
	QWidget app = MyWindow();

	return app.execute();
}