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
#include "AStarPathGenerator.h"
#include "Character.h"
#include "Timer.h"

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
	Timer gameTimer;

	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;
	Renderable * levelRenderable;

	Character myCharacter;
	AStar::PathGenerator pather;

	GameNode * gNodes;
	int numOfGNodes;

	bool editorMode;
	bool editorMode_lastState;
	bool camOnCharacter;
	bool showAllConnections;
	bool showPath;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	Ray getMouseRay();

	int mainTextureId;
	void paintGL();
	void updatePath(glm::vec3 newPos) {

	}
public:
	void initializeGL();
	void init();
	void addDebugMenu(DebugMenuManager * datMenu);

	void loadGeo(const char * binaryFilePath);
	void loadGeoFromBinary(char * binaryData);

	void prepForLevel();

	void mouseMoveEvent(QMouseEvent* e);
	void moveCam(QKeyEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void mousePressEvent (QMouseEvent * e );
	void myUpdate();
};