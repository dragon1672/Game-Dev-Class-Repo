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


class MyGUI : public QWidget {
private:

	Q_OBJECT;

	MyWindow meScene;
	QTimer myTimer;
	DebugMenuManager debugMenu;
	QHBoxLayout debugArea;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void updateScene();
	void updateFromScene();

public:
	MyGUI() {
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);

		debugMenu.init(&debugArea);
		QBoxLayout * mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
		setLayout(mainLayout);
		
		meScene.setMinimumHeight(900);

		mainLayout->addLayout(&debugArea);
		
		mainLayout->addWidget(&meScene);
		
		meScene.init(&debugMenu);

		updateFromScene();
		this->resize(1200,800);
	}
private slots:
	void myUpdate();
};