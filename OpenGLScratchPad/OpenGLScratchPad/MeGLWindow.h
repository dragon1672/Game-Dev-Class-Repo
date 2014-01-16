#pragma once

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>
#include "Player.h"

class MeGLWindow : public QGLWidget
{
private:

	Q_OBJECT

	struct codeBlock { // used to store shader code
		GLuint id;
		char * code;
	};

	QTimer myTimer;
	GLuint programID;

	Player players[3];
	int numOfPlayers;

	void createTriange();
	void initShaders();
	void initPlayers();
	void loadShader(char * code, GLuint id, bool debug=false);
	int buildProgram(int numOfFiles, codeBlock * arrayOfBlocks, bool debug=false);
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};

