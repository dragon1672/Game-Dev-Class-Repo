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

	QBoxLayout * mainLayout;
	QMenu * fileMenu;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	MyGUI()
	: toggleDebugMenu(TIDLE_KEY)
	{
		//setup layout
		QVBoxLayout *layout = new QVBoxLayout;
		//setup mainwidget
		QWidget * window = new QWidget();
        window->setLayout(layout);

		//set up locals
		myDebugMenu = new DebugMenuManager();
		myDebugMenu->init();

		meScene.setMinimumHeight(900);
		meScene.init();
		meScene.addDebugMenu(myDebugMenu);

		//add local widgets
		layout->addWidget(myDebugMenu);
		layout->addWidget(&meScene);
		fileMenu = menuBar()->addMenu("File");

        // Set QWidget as the central layout of the main window
        setCentralWidget(window);

		this->resize(1200,800);

		//setting up file actions
		QAction* action;
		fileMenu->addAction(action = new QAction("Load Object File", this));
		action->setShortcut(QKeySequence::Open);
		connect(action, SIGNAL(triggered()), this, SLOT(loadObj()));

		fileMenu->addAction(action = new QAction("Load Binary File", this));
		connect(action, SIGNAL(triggered()), this, SLOT(loadBin()));

		fileMenu->addAction(action = new QAction("Load Level File", this));
		action->setShortcuts(QKeySequence::Open);
		connect(action, SIGNAL(triggered()), this, SLOT(loadLevel()));

		fileMenu->addAction(action = new QAction("Save Level File", this));
		action->setShortcuts(QKeySequence::Save);
		connect(action, SIGNAL(triggered()), this, SLOT(saveNative()));
	}
private slots:
	void loadObj();
	void loadBin();
	void loadLevel();
	void saveNative();
};