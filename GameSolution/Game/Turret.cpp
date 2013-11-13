#include "Shape.h"
#include "Turret.h"
#include "MyRandom.h"
#include "GameSpace.h"
Core::RGB Turret::defaultTurretColor= RGB(255,255,255);

const float bulletScale = 4;
Shape Turret::defaultBulletStyle(RGB(255,0,255),
	Matrix3D::scaleY(-1) * Matrix3D::scale(bulletScale), 
	5,
	Vector2D(   .7f, -1.0f ),
	Vector2D(  0.0f,  1.0f ),
	Vector2D(  -.6f, -1.0f ),
	Vector2D(  1.0f,   .25f),
	Vector2D( -1.0f,   .25f) 
);
void Turret::shoot(Bullet *toShoot) {
	space->addBullet(toShoot);
}
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape defaultTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		3,
		Vector2D(-5,-2),
		Vector2D( 5,-2),
		Vector2D( 0,13)
);
//testing
Shape *Turret::getStyle() {
	return &defaultTurretStyle;
}
void Turret::update(float dt, const Vector2D& pos) {
	pointToMouse(pos);
	dt;
}

Vector2D Turret::tipOfTurret() {
	float turrentLenght = getStyle()->getMinY();
	return turrentLenght * direction;
}

void Turret::init(GameSpace *mySpace) {
	space = mySpace;
}
void Turret::pointToMouse(const Vector2D& pos) {
	direction = pos - Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
	direction = direction.normalized();
}

void Turret::draw(Core::Graphics& graphics, const Vector2D& pos) {
	Matrix3D transform = Matrix3D::translate(pos) * Matrix3D::rotateToVector(direction);
	getStyle()->draw(graphics, transform);
}