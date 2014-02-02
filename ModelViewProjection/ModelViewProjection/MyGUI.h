#pragma once

#include <Qt\qtimer.h>

#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include <QtGui\qcheckbox.h>
#include <QtGui\qlabel.h>
#include "DebugSlider.h"
#include "MyWindow.h"


class MyGUI : public QWidget {
private:

	Q_OBJECT;

	MyWindow meScene;
	QTimer myTimer;

	QCheckBox overrideColorEnabled_checkBox;
	QCheckBox inFragmentShaderLighting_checkBox;
	QCheckBox showLightSource_checkBox;

	QLabel overrideColor_LBL;
	DebugSlider overrideColor_R;
	DebugSlider overrideColor_G;
	DebugSlider overrideColor_B;

	QLabel diffPos_LBL;
	DebugSlider diffPos_X;
	DebugSlider diffPos_Y;
	DebugSlider diffPos_Z;

	QLabel diffCol_LBL;
	DebugSlider diffCol_R;
	DebugSlider diffCol_G;
	DebugSlider diffCol_B;

	QLabel ambCol_LBL;
	DebugSlider ambCol_R;
	DebugSlider ambCol_G;
	DebugSlider ambCol_B;


protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void updateScene();
	void updateFromScene();


	void setOverrideColor(glm::vec3 toSet);
	void setDiffPos(glm::vec3 toSet);
	void setDiffCol(glm::vec3 toSet);
	void setAmbCol(glm::vec3 toSet);
	void overrideColorEnabled(bool toSet);
	void inFragmentShaderLighting(bool toSet);
	void showLightSource(bool toSet);

public:
	MyGUI()
	: showLightSource_checkBox("Display Light Source"),
	overrideColor_LBL("Overriding Color"),
	overrideColor_R(0,1,true),
	overrideColor_G(0,1,true),
	overrideColor_B(0,1,true),

	diffPos_LBL("Diffuse Position"),
	diffPos_X(-1.5*meScene.range,1.5*meScene.range,true),
	diffPos_Y(-1.5*meScene.range,1.5*meScene.range,true),
	diffPos_Z(-1.5*meScene.range,1.5*meScene.range,true),

	diffCol_LBL("Diffuse Color"),
	diffCol_R(0,1,true),
	diffCol_G(0,1,true),
	diffCol_B(0,1,true),

	ambCol_LBL("Ambient Color"),
	ambCol_R(0,1,true),
	ambCol_G(0,1,true),
	ambCol_B(0,1,true),

	overrideColorEnabled_checkBox("Override Default Colors"),
	inFragmentShaderLighting_checkBox("Lighting in Fragment Shader")
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);
		//QBoxLayout * mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
		QGridLayout * mainLayout = new QGridLayout();
		setLayout(mainLayout);
		
		mainLayout->addWidget(&overrideColor_LBL,0,0);
		mainLayout->addWidget(&overrideColor_R,0,1);
		mainLayout->addWidget(&overrideColor_G,0,2);
		mainLayout->addWidget(&overrideColor_B,0,3);
		mainLayout->addWidget(&overrideColorEnabled_checkBox,0,4);

		mainLayout->addWidget(&diffPos_LBL,1,0);
		mainLayout->addWidget(&diffPos_X,1,1);
		mainLayout->addWidget(&diffPos_Y,1,2);
		mainLayout->addWidget(&diffPos_Z,1,3);

		mainLayout->addWidget(&diffCol_LBL,2,0);
		mainLayout->addWidget(&diffCol_R,2,1);
		mainLayout->addWidget(&diffCol_G,2,2);
		mainLayout->addWidget(&diffCol_B,2,3);

		mainLayout->addWidget(&ambCol_LBL,3,0);
		mainLayout->addWidget(&ambCol_R,3,1);
		mainLayout->addWidget(&ambCol_G,3,2);
		mainLayout->addWidget(&ambCol_B,3,3);

		mainLayout->addWidget(&inFragmentShaderLighting_checkBox,4,0);
		mainLayout->addWidget(&showLightSource_checkBox,4,1);

		mainLayout->addWidget(&meScene,5,0,mainLayout->rowCount(),mainLayout->columnCount());
		
		mainLayout->setRowMinimumHeight(100,10);

		meScene.init();

		updateFromScene();
		this->resize(1200,800);
	}
	glm::vec3 getOverrideColor();
	glm::vec3 getDiffPos();
	glm::vec3 getDiffCol();
	glm::vec3 getAmbCol();

	bool overrideColorEnabled();
	bool inFragmentShaderLighting();
	bool showLightSource();
private slots:
	void myUpdate();
};