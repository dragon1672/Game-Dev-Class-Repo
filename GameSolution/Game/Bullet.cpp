#include "Bullet.h"

void Bullet::setVel(const Vector2D& newVel) {
	vel = newVel;
	velNorm = vel.normalized();
}
void     Bullet::update(float dt) {
	pos = pos + vel*dt;
}
void    Bullet::draw(Core::Graphics graphics) {
	style->draw(graphics,Matrix3D::translate(pos) * Matrix3D::rotateToVector(-velNorm));
}