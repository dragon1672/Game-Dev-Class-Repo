#include "TurretMark5.h"
#include "Bullet.h"
#include <cmath>
#include "MyRandom.h"


const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark5Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		11,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 2),	Vector2D( 6, 6),
		Vector2D( 1,13),	Vector2D( 3, 5),	Vector2D( 0, 2),	Vector2D(-3, 5),
		Vector2D(-1,13),	Vector2D(-6, 6),	Vector2D(-6, 2)
);
Shape *TurretMark5::getStyle() {
	return &TurretMark5Style;
}

void TurretMark5::fireBullet() {
	Bullet createdBullet;
	createdBullet.pos   = myPos->getPos() + tipOfTurret();
	createdBullet.setVel(defaultBulletSpeed*(direction + Random::randomFloat(0,.1)*Random::randomUnitVector()));
	createdBullet.style = &defaultBulletStyle;
	shoot(&createdBullet);
}
float TurretMark5::getFireSpeed() {
	return .08f;
}