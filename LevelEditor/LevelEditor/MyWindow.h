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

	Renderable floor;
	Renderable lightSource;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	int mainTextureId;
	void paintGL();
	
	void saveDataDownToShader(ShaderProgram& prog);
	void generateRandomRenderable(uint count, GeometryInfo ** randomModels, uint randomModelCount);
	void registerInDebugMenu();
public:
	void initializeGL();
	void init(DebugMenuManager * debugMenu);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
	void draw(Renderable& entity,bool passthrough);
};