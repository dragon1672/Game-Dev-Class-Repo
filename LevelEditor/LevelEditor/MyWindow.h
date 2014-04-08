#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Renderer.h"
#include "DebugShapeManager.h"
#include "DebugMenuManager.h"

class MyWindow : public QGLWidget {
public:
	static const int range = 50;
private:

	Q_OBJECT;

	Renderer myRender;
	DebugShapeManager myDebugShapes;

	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	void paintGL();
	
public:
	void initializeGL();
	void init();
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};