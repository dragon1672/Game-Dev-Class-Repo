#include "Shape.h"
#include "Turret.h"
#include "MyRandom.h"
#include "GameSpace.h"
Core::RGB Turret::defaultTurretColor= RGB(255,255,255);
/*
Core::RGB defaultTurretColor = RGB(255,255,255);
const float GENERAL_STYLE_SCALE = 2;
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-GENERAL_STYLE_SCALE) * Matrix3D::scaleX(GENERAL_STYLE_SCALE);
Shape turretStyles[] = {
	Shape( defaultTurretColor, Cartesian2Screen, 11,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 4),	Vector2D( 3, 4),	Vector2D( 0,13),	Vector2D(-3, 4),
		Vector2D(-1, 4),	Vector2D(-1, 2),	Vector2D(-3, 2)
	), Shape( defaultTurretColor, Cartesian2Screen, 16,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 9),	Vector2D( 3,10),	Vector2D( 3,13),	Vector2D( 1,13),
		Vector2D( 1,11),	Vector2D(-1,11),	Vector2D(-1,13),	Vector2D(-3,13),
		Vector2D(-3,10),	Vector2D(-1, 9),	Vector2D(-1, 2),	Vector2D(-3, 2)
	), Shape( defaultTurretColor, Cartesian2Screen, 17,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 4, 1),	Vector2D( 4,10),
		Vector2D( 5,10),	Vector2D( 3,13),	Vector2D( 1,10),	Vector2D( 2,10),
		Vector2D( 3, 4),	Vector2D( 0, 2),	Vector2D(-3, 4),	Vector2D(-2,10),
		Vector2D(-1,10),	Vector2D(-3,13),	Vector2D(-5,10),	Vector2D(-4,10),
		Vector2D(-4, 1)
	), Shape(defaultTurretColor, Cartesian2Screen, 13,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 5),	Vector2D( 6,11),
		Vector2D( 3,13),	Vector2D( 1,12),	Vector2D( 3, 9),	Vector2D( 0, 3),
		Vector2D(-3, 9),	Vector2D(-1,12),	Vector2D(-3,13),	Vector2D(-6,11),
		Vector2D(-6, 5)
	), Shape( defaultTurretColor, Cartesian2Screen, 11,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 2),	Vector2D( 6, 6),
		Vector2D( 1,13),	Vector2D( 3, 5),	Vector2D( 0, 2),	Vector2D(-3, 5),
		Vector2D(-1,13),	Vector2D(-6, 6),	Vector2D(-6, 2)
	)
};//*/
void Turret::shoot(Bullet *toShoot) {
	space->addBullet(toShoot);
}
void Turret::init(GameSpace *mySpace) {
	space = mySpace;
}
void Turret::pointToMouse(const Vector2D& pos) {
	direction = pos - Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
}

void Turret::draw(Core::Graphics& graphics, const Vector2D& pos) {
	Matrix3D transform = Matrix3D::translate(pos) * Matrix3D::rotateToVector(direction.normalized());
	getStyle()->draw(graphics, transform);
}