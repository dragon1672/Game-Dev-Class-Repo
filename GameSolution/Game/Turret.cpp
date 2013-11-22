#include "Shape.h"
#include "Turret.h"
#include "MyRandom.h"
#include "GameSpace.h"
Core::RGB Turret::defaultTurretColor= RGB(255,255,255);
float Turret::defaultBulletSpeed = -100;

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

const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape defaultTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		3,
		Vector2D(-5,-2),
		Vector2D( 5,-2),
		Vector2D( 0,13)
);


//default
Shape *Turret::getStyle() {
	return &defaultTurretStyle;
}

//could be at a child level, but it is used a lot
Vector2D Turret::tipOfTurret() {
	float turrentLenght = getStyle()->getMinY();
	return turrentLenght * direction;
}

void Turret::pointToTarget() {
	direction = myPos->getPos() - target->getPos();
	direction = (direction).normalized();
	if(direction.lengthSquared()==0) direction = Vector2D(0,1);
}
void Turret::shoot(Bullet *toShoot) {
	toShoot->team = this->team;
	space->addBullet(toShoot);
}

//changing vars
void Turret::init(GameSpace *myWorld, DynamicPosition *location, DynamicPosition *target, FireLogic* logic, int team) {
	setFireLogic(logic);
	setTarget(target);
	changePos(location);
	this->space = myWorld;
	this->team  = team;
}
void Turret::setFireLogic(FireLogic *toSet) {
	this->myFireLogic = toSet;
}
void Turret::setTarget(DynamicPosition * toSet) {
	this->target = toSet;
}
void Turret::changePos(DynamicPosition * toSet) {
	this->myPos = toSet;
}

//core items
void Turret::update(float dt) {
	pointToTarget();
	timeSinceLastShot += dt;
	if(timeSinceLastShot>getFireSpeed() && myFireLogic->fired()) {
		timeSinceLastShot = 0;
		fireBullet();
	}
}
void Turret::draw(Core::Graphics& graphics) {
	Matrix3D transform = Matrix3D::translate(myPos->getPos()) * Matrix3D::rotateToVector(direction);
	getStyle()->draw(graphics, transform);
}
int  Turret::getTeam() {
	return team;
}
Vector2D Turret::getPos() {
	return myPos->getPos();
}