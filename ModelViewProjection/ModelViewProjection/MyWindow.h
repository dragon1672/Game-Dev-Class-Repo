#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"
#include "DrawnObj.h"
#include "GameObj.h"
#include "Camera.h"
#include "Renderer.h"

class MyWindow : public QGLWidget {
public:
	static const int range = 25;
private:

	Q_OBJECT;

	Renderer myRender;

	QTimer myTimer;
	Camera myCam;

	Renderable * gameObjs[1000];
	uint numOfGameObjs;

	Renderable floor;
	Renderable lightSource;

	void sendDataToHardWare();
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

	bool  enableTexture;
	bool  enableLighting;
	
	//changes display and update
	bool displayLightEntity;
	bool objectsMoving;

	void paintGL();
	void init();
private:
	void passDataDownToShader(ShaderProgram& prog, bool passthrough);
public:
	void initializeGL();
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void myUpdate();
	void draw(Renderable& entity,bool passthrough);
};