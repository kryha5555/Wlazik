#include "..\include\Lazik.h"


Lazik::Lazik(GLfloat x, GLfloat y, GLfloat z, GLfloat lenx, GLfloat leny, GLfloat lenz)
	: Figura(x, y, z)
	, xlen{ lenx }
	, ylen{ leny }
	, zlen{ lenz }
{
	setParams();
}

Lazik::~Lazik()
{
}

void Lazik::draw()
{
	//left right front middle rear
	Walec lfWheel(xpos, ypos + ylen, zpos, wheelRadius, -wheelHeight);
	Walec lmWheel(xpos, ypos + ylen / 3, zpos, wheelRadius, -wheelHeight);
	Walec lrWheel(xpos, ypos, zpos, wheelRadius, -wheelHeight);

	wheels.insert(wheels.end(), { lfWheel,lmWheel,lrWheel });

	Walec rfWheel(xpos + xlen + 4 * axleRadius, ypos + ylen, zpos, wheelRadius, wheelHeight);
	Walec rmWheel(xpos + xlen + 4 * axleRadius, ypos + ylen / 3, zpos, wheelRadius, wheelHeight);
	Walec rrWheel(xpos + xlen + 4 * axleRadius, ypos, zpos, wheelRadius, wheelHeight);
	// minus na lewych kolach, aby zachowac punkt poczatkowy w srodku lewego tylnego kola

	wheels.insert(wheels.end(), { rfWheel,rmWheel,rrWheel });
	//TODO: znalezc lepszy pomysl na to ^

	for (auto wheel : wheels)
	{
		wheel.setColor(1, 0, 0);
		wheel.draw();
	}

	//front top bottom vertical rear
	Walec lfAxle(xpos, ypos + ylen, zpos, axleRadius, xpos + 2 * axleRadius, ypos + (2.f / 3.f)*ylen, zpos + platformEvelation + platformThickness / 2);
	Walec ltAxle(xpos + axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation, axleRadius, xpos + 2 * axleRadius, ypos + (2.f / 3.f)*ylen, zpos + platformEvelation + platformThickness / 2);
	Walec lbAxle(xpos, ypos + ylen / 3, zpos, axleRadius, xpos + axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation);
	Walec lvAxle(xpos + axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation, axleRadius, xpos + 2*axleRadius, ypos + ylen / 6, zpos + platformEvelation + platformThickness / 2);
	Walec lrAxle(xpos, ypos, zpos, axleRadius, xpos + axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation);
	axles.insert(axles.end(), { lfAxle,ltAxle,lbAxle,lvAxle,lrAxle });

	Walec rfAxle(xpos + xlen + 4 * axleRadius, ypos + ylen, zpos, axleRadius, xpos + +xlen+2 * axleRadius, ypos + (2.f / 3.f)*ylen, zpos + platformEvelation + platformThickness / 2);
	Walec rtAxle(xpos + xlen + 3 * axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation, axleRadius, xpos +xlen+ 2 * axleRadius, ypos + (2.f / 3.f)*ylen, zpos + platformEvelation + platformThickness / 2);
	Walec rbAxle(xpos + xlen + 4 * axleRadius, ypos + ylen / 3, zpos, axleRadius, xpos +xlen+ 3*axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation);
	Walec rvAxle(xpos + xlen+3*axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation, axleRadius, xpos+xlen + 2 * axleRadius, ypos + ylen / 6, zpos + platformEvelation + platformThickness / 2);
	Walec rrAxle(xpos + xlen + 4 * axleRadius, ypos, zpos, axleRadius, xpos +xlen+ 3*axleRadius, ypos + ylen / 6, zpos + (2.f / 3.f)*platformEvelation);
	axles.insert(axles.end(), { rfAxle,rtAxle,rbAxle,rvAxle,rrAxle });
	//TODO: znalezc lepszy pomysl na to ^

	for (auto axle : axles)
	{
		axle.setColor(0, 0, 1);
		axle.draw();
	}

	Szescian platform(xpos + 2 * axleRadius, ypos, zpos + platformEvelation, xlen, ylen, zpos + platformThickness);
	platform.setColor(0, 1, 0);
	platform.draw();

}

void Lazik::setParams()
{
	//TODO: parametryzacja i opis

	wheelRadius = 8;
	wheelHeight = 10;
	axleRadius = wheelHeight / 5;
	axleHeight = xlen + 4 * axleRadius;
	platformEvelation = 20;
	platformThickness = 5;

}
