#pragma once

#include <QtOpenGL\qglwidget>

class MeGLWindow : public QGLWidget
{
private:
	void createTriange();
	void initShaders();
	void loadShader(char * code, GLuint id);
protected:
	void initializeGL();
	void paintGL();
public:
};

