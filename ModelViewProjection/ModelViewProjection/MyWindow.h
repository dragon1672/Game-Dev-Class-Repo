#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "DrawnObj.h"
#include "GameObj.h"
#include "Camera.h"

class MyWindow : public QGLWidget {
	
	Q_OBJECT

	ShaderProgram myShadyShader;
	QTimer myTimer;
	Camera myCam;

	DrawnObj myShapes[10];
	int numOfShapes;

	GameObj myGameObjs[50];
	int numOfGameObjs;

	void sendDataToHardWare();
	void initShaders();

protected:
	void initializeGL();
	void paintGL();
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};