#include "GameEntity.h"

Shape*   GameEntity::getStyle() { return NULL; }
Matrix3D GameEntity::getTransMatrix() {
	return Matrix3D();
}
void     GameEntity::update(float dt) {
	dt;
}
void     GameEntity::draw(Core::Graphics& graphics) {
	getStyle()->draw(graphics,getTransMatrix());
}