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
	DebugMenuManager * debugMenu;


	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;
	Renderable * levelRenderable;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	int mainTextureId;
	void paintGL();
public:
	void initializeGL();
	void init(DebugMenuManager * debugMenu);
	void loadGeo(const char * binaryFilePath);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};