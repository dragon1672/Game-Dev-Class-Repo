#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Renderer.h"
#include "DebugShapeManager.h"
#include "Ray.h"
#include "AStarPathGenerator.h"
#include "Character.h"
#include "AStarDebugPath.h"
#include "DebugMenuManager.h"
#include "AStarDebugPathGenerator.h"
#include "Timer.h"

class MyWindow : public QGLWidget {
	static const char * fileName;
public:
	static const int range = 50;
private:

	Q_OBJECT;

	Renderer myRender;
	DebugShapeManager myDebugShapes;
private:
	Timer myTimer;

	QTimer updateTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;
	Renderable * levelRenderable;
	GameNode * nodes;
	uint numOfNodes;

	Character myCharacter;
	bool camOnCharacter;

	bool showAllConnections;
	bool showAllConnections_lastState;
	bool showPath;
	bool showPath_lastState;

	AStar::DEBUG::AStarDebugPathGenerator pather;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	Ray getMouseRay();

	int mainTextureId;
	void paintGL();
public:
	void initializeGL();
	void init();
	void addDebugMenu(DebugMenuManager * datMenu);
	void loadLevel(const char * filePath);
	void loadGeoFromBinary(char * binaryData);

	void prepForLevel();

	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};