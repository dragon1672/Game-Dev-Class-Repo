#pragma once
#include <QtOpenGL\qglwidget>

class MeGLWindow : public QGLWidget {
protected:
	void initializeGL();
	void paintGL();
public:

};