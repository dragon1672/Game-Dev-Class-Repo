#include "Shape.h"
#include "Turret.h"
#include "MyRandom.h"
#include "GameSpace.h"
Core::RGB Turret::defaultTurretColor= RGB(255,255,255);
float Turret::defaultBulletSpeed = -100;

const float bulletScale = 4;
void Turret::shootBullet(Bullet *toShoot) {
	space->addBullet(toShoot);
}
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1); /*Cartesian2Screen seems like a good name, but consider whether or not everyone will understand what you mean*/
const float turretScale = 2.5;
Shape defaultTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		3,
		Vector2D(-5,-2),
		Vector2D( 5,-2),
		Vector2D( 0,13)
);

Shape *Turret::getStyle() {
	return &defaultTurretStyle;
}
void Turret::update(float dt) {
	pointToMouse();
	dt;
}
bool Turret::shoot() {
	bool shot = false;
	for(int i=0;i<getMaxBullets() && !shot;i++) {
		shot = !startOfArray()[i].isActive();
		if(shot) initBullet(i);
	}
	return shot;
}
Vector2D Turret::tipOfTurret() {
	float turrentLenght = getStyle()->getMinY();
	return turrentLenght * direction;
}
Vector2D Turret::getParentPos() {
	return parent->getTransMatrix() * Vector2D(0,0);
}
void Turret::init(GameSpace *mySpace, GameEntity *parent) {
	space = mySpace;
	this->parent = parent;
}
void Turret::pointToMouse() {
	direction = getParentPos() - Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
	direction = (direction).normalized();
}

void Turret::draw(Core::Graphics& graphics) {
	Matrix3D transform = Matrix3D::translate(getParentPos()) * Matrix3D::rotateToVector(direction);
	getStyle()->draw(graphics, transform);
}