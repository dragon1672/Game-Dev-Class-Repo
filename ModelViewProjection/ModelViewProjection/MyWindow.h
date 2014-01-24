#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

#include "ShaderProgram.h"

class MyWindow : public QGLWidget {
	
	Q_OBJECT

	ShaderProgram myShadyShader;

	QTimer myTimer;

	void sendDataToHardWare();
	void initShaders();

protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};