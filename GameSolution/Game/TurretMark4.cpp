#include "TurretMark4.h"
#include "Bullet.h"
#include <cmath>
#include "MyRandom.h"

const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark4Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		13,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 5),	Vector2D( 6,11),
		Vector2D( 3,13),	Vector2D( 1,12),	Vector2D( 3, 9),	Vector2D( 0, 3),
		Vector2D(-3, 9),	Vector2D(-1,12),	Vector2D(-3,13),	Vector2D(-6,11),
		Vector2D(-6, 5)
);


Shape *TurretMark4::getStyle() {
	return &TurretMark4Style;
}

void TurretMark4::fireBullet() {//fires 7 shots
	Bullet createdBullet;
	createdBullet.pos   = myPos->getPos() + tipOfTurret();
	createdBullet.style = &defaultBulletStyle;
	for(int i=0;i<NUM_OF_SHOTS;i++) {
		createdBullet.setVel(defaultBulletSpeed/2*(2*direction + Random::randomFloat(0,.75)*Random::randomUnitVector()));
		shoot(&createdBullet);
	}
}
float TurretMark4::getFireSpeed() {
	return 1.2f;
}