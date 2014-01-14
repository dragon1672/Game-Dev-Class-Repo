#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

class MeGLWindow : public QGLWidget
{
private:

	Q_OBJECT

	struct codeBlock { // used to store shader code
		GLuint id;
		char * code;
	};

	void createTriange();
	void initShaders();
	void loadShader(char * code, GLuint id, bool debug=false);
	int buildProgram(int numOfFiles, codeBlock * arrayOfBlocks, bool debug=false);
	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};

