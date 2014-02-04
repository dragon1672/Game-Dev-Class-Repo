#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "DrawnObj.h"
#include "GameObj.h"
#include "Camera.h"

class MyWindow : public QGLWidget {
public:
	static const int range = 25;
private:

	Q_OBJECT

	ShaderProgram myShadyShader;
	QTimer myTimer;
	Camera myCam;

	GameObj myGameObjs[200];
	int numOfGameObjs;

	GameObj camEntity;
	GameObj floor;

	void sendDataToHardWare();
	void initShaders();
public: // interface to editVals
	//shader info
	bool enableOverrideColor;
	glm::vec3 overrideColor;
	glm::vec3 ambientLight;
	glm::vec3 diffuseLight;
	glm::vec3 diffusePos;
	glm::vec3 specColor;
	float specPower;
	//preforms calculations in fragment shader
	bool diffuseInFrag;
	
	//changes display and update
	bool displayLightEntity;
	bool objectsMoving;

	void paintGL();
	void init();

public:
	void initializeGL();
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
	void draw(GameObj& entity);
};