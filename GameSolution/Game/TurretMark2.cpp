#include "TurretMark2.h"
#include "Bullet.h"
#include <cmath>
#include "MyRandom.h"


const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark2Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		16,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 9),	Vector2D( 3,10),	Vector2D( 3,13),	Vector2D( 1,13),
		Vector2D( 1,11),	Vector2D(-1,11),	Vector2D(-1,13),	Vector2D(-3,13),
		Vector2D(-3,10),	Vector2D(-1, 9),	Vector2D(-1, 2),	Vector2D(-3, 2)
);


Shape *TurretMark2::getStyle() {
	return &TurretMark2Style;
}

void TurretMark2::fireBullet() {
		Bullet createdBullet;
		createdBullet.pos   = myPos->getPos() + tipOfTurret();
		createdBullet.setVel((defaultBulletSpeed*direction) + Random::randomFloatVector(0,3));
		createdBullet.style = &defaultBulletStyle;
		shoot(&createdBullet);
}
float TurretMark2::getFireSpeed() {
	return .125;
}