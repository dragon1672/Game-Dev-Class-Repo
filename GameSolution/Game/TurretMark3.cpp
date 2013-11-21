#include "TurretMark3.h"
#include "Bullet.h"
#include <cmath>


const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark3Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		17,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 4, 1),	Vector2D( 4,10),
		Vector2D( 5,10),	Vector2D( 3,13),	Vector2D( 1,10),	Vector2D( 2,10),
		Vector2D( 3, 4),	Vector2D( 0, 2),	Vector2D(-3, 4),	Vector2D(-2,10),
		Vector2D(-1,10),	Vector2D(-3,13),	Vector2D(-5,10),	Vector2D(-4,10),
		Vector2D(-4, 1)
);

Shape arrow(RGB(255,0,255),
			Cartesian2Screen * Matrix3D::scale(1),
			7,
			Vector2D(-1,0),
			Vector2D( 1,0),
			Vector2D( 1,4),
			Vector2D( 3,4),
			Vector2D( 0,8),//point
			Vector2D(-3,4),
			Vector2D(-1,4)
);

Shape *TurretMark3::getStyle() {
	return &TurretMark3Style;
}

void TurretMark3::fireBullet() {
	const float distBetweenBullets = 18;
	Bullet createdBullet;
	Matrix3D turretRotation = Matrix3D::rotateToVector(direction);
	//offset from center with turret rotation
	Vector2D offset = turretRotation * Vector2D(distBetweenBullets/2,0);

	createdBullet.pos   = myPos->getPos() + offset + tipOfTurret();
	createdBullet.setVel(defaultBulletSpeed*direction);
	createdBullet.style = &arrow;
	shoot(&createdBullet);

	//offset from center with turret rotation (other side)
	offset = turretRotation * Vector2D(-distBetweenBullets/2,0);
	createdBullet.pos   = myPos->getPos() + offset + tipOfTurret();
	shoot(&createdBullet);
}
float TurretMark3::getFireSpeed() {
	return .2;
}