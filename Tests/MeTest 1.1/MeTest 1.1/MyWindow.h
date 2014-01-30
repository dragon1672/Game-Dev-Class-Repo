#pragma once

#include <QtOpenGL\qglwidget>
#include "SingleBuffObj.h"
#include "Camera.h"
#include "GameObj.h"

class MyWindow : public QGLWidget {
private:
	SingleBuffObj myShapes[10];
	//uint numOfShapes;

	GameObj myGameThings[1000];
	uint numOfThings;

protected:
	void initializeGL();
	void sendDataToHardware();

	void initShaders();

	GLint programID;
	GLuint bufferID;

	Camera myCam;



	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);

public:
	void paintGL();
};