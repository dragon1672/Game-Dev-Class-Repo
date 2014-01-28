#pragma once

#include <qt/qapplication.h>
#include <Qt/qwidget.h>
#include <QtGui\qwidget.h>
#include <QtGui\qpixmap.h>
#include <QtOpenGL\qglwidget>
#include "Camera.h"
#include "SingleBufferShape.h"

class MyWindow : public QGLWidget {
private:
	Camera myCam;
	SingleBufferShape myShapes[5];
	int numOfShapes;


protected:
	void initializeGL();
	void sendDataToHardware();
	void paint();
};