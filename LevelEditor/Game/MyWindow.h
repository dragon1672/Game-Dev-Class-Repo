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

class MyWindow : public QGLWidget {
	static const char * fileName;
public:
	static const int range = 50;
private:

	Q_OBJECT;

	Renderer myRender;
	DebugShapeManager myDebugShapes;
private:

	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;
	Renderable * levelRenderable;
	GameNode * nodes;
	uint numOfNodes;

	Character myCharacter;

	AStar::PathGenerator pather;

	void sendDataToHardWare();

	//shader info
	glm::mat4 viewTransform;

	Ray getMouseRay();

	int mainTextureId;
	void paintGL();
public:
	void initializeGL();
	void init();
	void loadLevel(const char * filePath);
	void loadGeoFromBinary(char * binaryData);

	void prepForLevel();

	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
};