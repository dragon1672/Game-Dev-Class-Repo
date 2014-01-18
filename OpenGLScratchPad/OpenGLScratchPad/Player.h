#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

class Player {
private:
	static glm::vec4 acc;
	static float SPEED;
	static float SCALE;
	static float angleAcc;

	glm::vec3 translation;
	float angle;
	//keys
	int accKey;
	int decKey;
	int rotLKey;
	int rotRKey;

	glm::vec3 col;

	float getRandomSpawnAngle();

	int points;
public:
	void initPlayer(glm::vec3 color, glm::vec3 pos, int accelerate='w', int deccelerate='s', int rotateLeft = 'a', int rotateRight='d');

	void update();

	glm::mat4x4 getTransform();
	glm::vec3 getColor();

	bool isColliding2D(glm::vec3 pos, float theirRad);
	bool isColliding2D(Player& that);
	bool isColliding3D(glm::vec3 pos, float theirRad);
	bool isColliding3D(Player& that);

	void addPoint();
	int getPoints();

	void setDepth(float pos);
};

#endif