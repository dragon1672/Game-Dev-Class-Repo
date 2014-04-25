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

	MyWindow meScene;

	QBoxLayout * mainLayout;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	MyGUI()
	{
		meScene.setMinimumHeight(900);
		setCentralWidget(&meScene);
		
		meScene.init();

		this->resize(1200,800);
	}
};