#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "DrawnObj.h"
#include "GameObj.h"

class MyWindow : public QGLWidget {
	
	Q_OBJECT

	ShaderProgram myShadyShader;
	QTimer myTimer;

	DrawnObj myShapes[10];
	int numOfShapes;

	GameObj myGameObjs[50];
	int numOfGameObjs;

	void sendDataToHardWare();
	void initShaders();

protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};