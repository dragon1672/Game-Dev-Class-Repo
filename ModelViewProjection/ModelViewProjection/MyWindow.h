#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "DrawnObj.h"
#include "GameObj.h"
#include "Camera.h"

class MyWindow : public QGLWidget {
public:
	static const int range = 10;
private:

	Q_OBJECT

	ShaderProgram myShadyShader;
	QTimer myTimer;
	Camera myCam;

	DrawnObj myShapes[6];
	int numOfShapes;

	GameObj myGameObjs[200];
	int numOfGameObjs;

	GameObj camEntity;
	GameObj floor;

	void sendDataToHardWare();
	void initShaders();
public: // interface to editVals
	bool enableOverrideColor;
	bool displayLightEntity;
	glm::vec3 overrideColor;
	glm::vec3 ambientLight;
	glm::vec3 diffuseLight;
	glm::vec3 diffusePos;
	bool diffuseInFrag;
	void paintGL();
	void init();

public:
	void initializeGL();
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
	void draw(GameObj& entity);
	void draw(GameObj * blockData, glm::mat4x4 lastTransform, float scale, int depth, int children, glm::vec3 orbitLength, glm::vec3 orbitAxis);
};