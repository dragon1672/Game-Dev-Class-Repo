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
	
	void saveDataDownToShader(ShaderProgram& prog);
	void generateRandomRenderable(uint count, GeometryInfo ** randomModels, uint randomModelCount, uint numOfTextures);
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