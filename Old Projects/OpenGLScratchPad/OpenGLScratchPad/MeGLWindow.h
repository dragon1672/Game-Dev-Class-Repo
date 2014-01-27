#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>
#include "Player.h"
#include "ShaderProgram.h"

class MeGLWindow : public QGLWidget
{
private:

	Q_OBJECT

	ShaderProgram myShadyShaders;

	QTimer myTimer;

	Player players[4];
	int numOfPlayers;

	void createTriange();
	void initPlayers();
	void initShaders();

protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};

