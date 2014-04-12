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

	QBoxLayout * mainLayout;
	QMenu * fileMenu;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	MyGUI()
	: toggleDebugMenu(TIDLE_KEY)
	{
		meScene.setMinimumHeight(900);
		setCentralWidget(&meScene);
		
		meScene.init();

		this->resize(1200,800);

		fileMenu = menuBar()->addMenu("File");

		QAction* action;
		fileMenu->addAction(action = new QAction("Load Object File", this));
		action->setShortcut(QKeySequence::Open);
		connect(action, SIGNAL(triggered()), this, SLOT(loadObj()));

		fileMenu->addAction(action = new QAction("Save Native File", this));
		action->setShortcuts(QKeySequence::Save);
		connect(action, SIGNAL(triggered()), this, SLOT(saveNative()));

		fileMenu->addAction(action = new QAction("Save Native File as...", this));
		//action->setShortcuts(QKeySequence::Save);
		connect(action, SIGNAL(triggered()), this, SLOT(saveNativeAs()));
	}
private slots:
	void loadObj();
	void saveNative();
	void saveNativeAs();
};