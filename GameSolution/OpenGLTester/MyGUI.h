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


class MyGUI : public QWidget {
private:
	static const int TIDLE_KEY = 192;

	Q_OBJECT;

	SingleKeyManager toggleDebugMenu;

	MyWindow meScene;
	QTimer myTimer;
	DebugMenuManager * debugMenu;

	QBoxLayout * mainLayout;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void updateScene();
	void updateFromScene();

public:
	MyGUI()
	: toggleDebugMenu(TIDLE_KEY)
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);

		debugMenu = new DebugMenuManager();

		debugMenu->init();
		mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
		setLayout(mainLayout);
		
		meScene.setMinimumHeight(900);

		mainLayout->addWidget(debugMenu);
		
		mainLayout->addWidget(&meScene);
		
		meScene.init(debugMenu);

		updateFromScene();
		this->resize(1200,800);
	}
private slots:
	void myUpdate();
};