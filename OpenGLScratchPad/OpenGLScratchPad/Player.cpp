#include "Player.h"
#include <Windows.h>
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::vec4 Player::acc(0,1,0,0);
float Player::SPEED = .02f;
float Player::SCALE = .3f;
float Player::angleAcc = 4;

using glm::vec3;

void Player::initPlayer(glm::vec3 color, glm::vec3 pos, int accelerate, int deccelerate, int rotateLeft, int rotateRight) {
	col = color;
	accKey  = accelerate;
	decKey  = deccelerate;
	rotLKey = rotateLeft;
	rotRKey = rotateRight;
	translation = pos;
	angle = 0;

	points = 0;
}


void Player::update() {
	if(GetAsyncKeyState(rotLKey)) {
		angle += angleAcc;
	} else if(GetAsyncKeyState(rotRKey)) {
		angle -= angleAcc;
	}
	if(GetAsyncKeyState(accKey)) {
		translation += SPEED * vec3(glm::rotate(angle,vec3(0,0,1)) * acc);
	} else if(GetAsyncKeyState(decKey)) {
		translation -= SPEED * vec3(glm::rotate(angle,vec3(0,0,1)) * acc);
	}
}

glm::mat4x4 Player::getTransform() {
	glm::mat4x4 transformation = glm::translate(translation);
	transformation *= glm::rotate(angle,vec3(0,0,1));
	transformation *= glm::scale(vec3(SCALE,SCALE,1));
	return transformation;
}
glm::vec3 Player::getColor() {
	return col;
}

bool Player::isColliding2D(vec3 pos, float theirRad) {
	vec3 diff = pos - translation;
	diff.z = 0;
	float length = glm::length(diff);
	float radLen = theirRad+SCALE;
	return length < radLen;
}
bool Player::isColliding2D(Player& that) {
	vec3 diff = that.translation - translation;
	diff.z = 0;
	float length = glm::length(diff);
	float radLen = that.SCALE+SCALE;
	return length < radLen;
}
bool Player::isColliding3D(vec3 pos, float theirRad) {
	vec3 diff = pos - translation;
	return diff.length()<(theirRad+SCALE);
}
bool Player::isColliding3D(Player& that) {
	vec3 diff = that.translation - translation;
	return diff.length()<(that.SCALE+SCALE);
}
void Player::addPoint() {
	points++;
}
int  Player::getPoints() {
	return points;
}
void Player::setDepth(float pos) {
	translation.z = pos;
}