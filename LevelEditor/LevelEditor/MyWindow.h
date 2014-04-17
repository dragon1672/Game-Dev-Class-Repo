#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Renderer.h"
#include "DebugShapeManager.h"
#include "DebugMenuManager.h"
#include "Ray.h"
#include "NodeManager.h"

class MyWindow : public QGLWidget {
public:
	static const int range = 50;
private:

	Q_OBJECT;

	Renderer myRender;
	DebugShapeManager myDebugShapes;
public:
	NodeManager myNodeManager;
private:

	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;
	Renderable * levelRenderable;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	void addNode(Ray& mouseRay);
	void nodeOperationClick();

	Ray getMouseRay();

	int mainTextureId;
	void paintGL();
public:
	void initializeGL();
	void init();
	void loadGeo(const char * binaryFilePath);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};