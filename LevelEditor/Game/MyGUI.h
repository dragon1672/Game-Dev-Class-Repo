#pragma once

#include <Qt\qtimer.h>

#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include <QtGui\qcheckbox.h>
#include <QtGui\qlabel.h>
#include "DebugSlider.h"
#include "LinkedSlider.h"
#include "MyWindow.h"
#include "DebugMenuManager.h"
#include "SingleKeyManager.h"
#include "Qt/qaction.h"
#include "Qt/qmenu.h"
#include "Qt/qmenubar.h"
#include "Qt/qmainwindow.h"


class MyGUI : public QMainWindow {
private:
	static const int TIDLE_KEY = 192;

	Q_OBJECT;

	SingleKeyManager toggleDebugMenu;

	MyWindow meScene;
	DebugMenuManager * myDebugMenu;
	QTimer myTimer;

	QMenu * fileMenu;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	MyGUI()
	: toggleDebugMenu(TIDLE_KEY)
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);


		//setup layout
		QVBoxLayout *layout = new QVBoxLayout;
		//setup mainwidget
		QWidget * window = new QWidget();
        window->setLayout(layout);

		//set up locals
		myDebugMenu = new DebugMenuManager();
		myDebugMenu->init();

		meScene.setMinimumHeight(700);
		meScene.setMinimumWidth(1200);
		meScene.init();
		meScene.addDebugMenu(myDebugMenu);

		//add local widgets
		layout->addWidget(myDebugMenu);
		layout->addWidget(&meScene);

		setCentralWidget(window);
	}
private slots:
	void myUpdate();
};