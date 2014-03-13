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
	MyGUI()
		/*
	: showLightSource_checkBox("Display Light Source"),
	overrideColor_LBL("Overriding Color"),
	overrideColor_R(&meScene.overrideColor.r, 0,1,true),
	overrideColor_G(&meScene.overrideColor.g, 0,1,true),
	overrideColor_B(&meScene.overrideColor.b, 0,1,true),

	diffPos_LBL("Diffuse Position"),
	diffPos_X(&meScene.diffusePos.x,-1.5*meScene.range,1.5*meScene.range,true),
	diffPos_Y(&meScene.diffusePos.y,-1.5*meScene.range,1.5*meScene.range,true),
	diffPos_Z(&meScene.diffusePos.z,-1.5*meScene.range,1.5*meScene.range,true),

	diffCol_LBL("Diffuse Color"),
	diffCol_R(&meScene.diffuseLight.r,0,1,true),
	diffCol_G(&meScene.diffuseLight.g,0,1,true),
	diffCol_B(&meScene.diffuseLight.b,0,1,true),

	ambCol_LBL("Ambient Color"),
	ambCol_R(&meScene.ambientLight.r,0,1,true),
	ambCol_G(&meScene.ambientLight.g,0,1,true),
	ambCol_B(&meScene.ambientLight.b,0,1,true),

	specCol_LBL("Spec Color"),
	specCol_R(&meScene.specColor.r,0,1,true),
	specCol_G(&meScene.specColor.g,0,1,true),
	specCol_B(&meScene.specColor.b,0,1,true),
	
	specPower_LBL("Spec Power"),
	specPower(&meScene.specPower,25,1000,true),

	overrideColorEnabled_checkBox("Override Default Colors"),
	moveObjects_checkBox("Allow Objects To Move"),
	enableTexture_checkBox("Enable Textures"),
	enableLighting_checkBox("Enable Lighting"),
	inFragmentShaderLighting_checkBox("Lighting in Fragment Shader")//*/
	{
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