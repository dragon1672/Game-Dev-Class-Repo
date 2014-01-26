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

	DrawnObj myShapes[6];
	int numOfShapes;

	GameObj myGameObjs[200];
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
	void draw(GameObj * blockData, glm::mat4x4 lastTransform, float scale, int depth, int children, glm::vec3 orbitLength, glm::vec3 orbitAxis);
};