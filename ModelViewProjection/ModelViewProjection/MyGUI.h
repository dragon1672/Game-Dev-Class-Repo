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


class MyGUI : public QWidget {
private:

	Q_OBJECT;

	MyWindow meScene;
	QTimer myTimer;

	QCheckBox overrideColorEnabled_checkBox;
	QCheckBox inFragmentShaderLighting_checkBox;
	QCheckBox showLightSource_checkBox;
	QCheckBox moveObjects_checkBox;

	QLabel overrideColor_LBL;
	LinkedSlider overrideColor_R;
	LinkedSlider overrideColor_G;
	LinkedSlider overrideColor_B;

	QLabel diffPos_LBL;
	LinkedSlider diffPos_X;
	LinkedSlider diffPos_Y;
	LinkedSlider diffPos_Z;

	QLabel diffCol_LBL;
	LinkedSlider diffCol_R;
	LinkedSlider diffCol_G;
	LinkedSlider diffCol_B;

	QLabel ambCol_LBL;
	LinkedSlider ambCol_R;
	LinkedSlider ambCol_G;
	LinkedSlider ambCol_B;

	QLabel specCol_LBL;
	LinkedSlider specCol_R;
	LinkedSlider specCol_G;
	LinkedSlider specCol_B;
	
	QLabel specPower_LBL;
	LinkedSlider specPower;
	


protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void updateScene();
	void updateFromScene();


	void setOverrideColor(glm::vec3 toSet);
	void setDiffPos(glm::vec3 toSet);
	void setDiffCol(glm::vec3 toSet);
	void setAmbCol(glm::vec3 toSet);
	void setSpecCol(glm::vec3 toSet);
	void setSpecPower(float toSet);

	void overrideColorEnabled(bool toSet);
	void inFragmentShaderLighting(bool toSet);
	void showLightSource(bool toSet);

public:
	MyGUI()
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
	inFragmentShaderLighting_checkBox("Lighting in Fragment Shader")
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);
		//QBoxLayout * mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
		QGridLayout * mainLayout = new QGridLayout();
		setLayout(mainLayout);
		
		int row = 0;

		mainLayout->addWidget(&overrideColor_LBL,row,0);
		mainLayout->addWidget(&overrideColor_R,row,1);
		mainLayout->addWidget(&overrideColor_G,row,2);
		mainLayout->addWidget(&overrideColor_B,row,3);

		row++;

		mainLayout->addWidget(&diffPos_LBL,row,0);
		mainLayout->addWidget(&diffPos_X,row,1);
		mainLayout->addWidget(&diffPos_Y,row,2);
		mainLayout->addWidget(&diffPos_Z,row,3);

		row++;

		mainLayout->addWidget(&diffCol_LBL,row,0);
		mainLayout->addWidget(&diffCol_R,row,1);
		mainLayout->addWidget(&diffCol_G,row,2);
		mainLayout->addWidget(&diffCol_B,row,3);

		row++;

		mainLayout->addWidget(&ambCol_LBL,row,0);
		mainLayout->addWidget(&ambCol_R,row,1);
		mainLayout->addWidget(&ambCol_G,row,2);
		mainLayout->addWidget(&ambCol_B,row,3);

		row++;

		mainLayout->addWidget(&specCol_LBL,row,0);
		mainLayout->addWidget(&specCol_R,row,1);
		mainLayout->addWidget(&specCol_G,row,2);
		mainLayout->addWidget(&specCol_B,row,3);

		row++;

		mainLayout->addWidget(&specPower_LBL,row,0);
		mainLayout->addWidget(&specPower,row,1);

		row++;

		QLabel * temp = new QLabel("Options");

		mainLayout->addWidget(temp,row,0);

		QHBoxLayout * checkBoxes = new QHBoxLayout();

		mainLayout->addLayout(checkBoxes,row,1);

		checkBoxes->addWidget(&inFragmentShaderLighting_checkBox);
		checkBoxes->addWidget(&showLightSource_checkBox);
		checkBoxes->addWidget(&overrideColorEnabled_checkBox);
		checkBoxes->addWidget(&moveObjects_checkBox);

		meScene.setMinimumHeight(800);

		row++;

		mainLayout->addWidget(&meScene,row,0,mainLayout->rowCount(),mainLayout->columnCount());
		
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