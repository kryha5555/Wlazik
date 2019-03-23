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
	Walec rfWheel(xpos + xlen, ypos + ylen, zpos, wheelRadius, wheelHeight);
	Walec lmWheel(xpos, ypos + ylen / 2, zpos, wheelRadius, -wheelHeight);
	Walec rmWheel(xpos + xlen, ypos + ylen / 2, zpos, wheelRadius, wheelHeight);
	Walec lrWheel(xpos, ypos, zpos, wheelRadius, -wheelHeight);
	Walec rrWheel(xpos + xlen, ypos, zpos, wheelRadius, wheelHeight);
	// minus na lewych ko³ach, aby zachowaæ punkt pocz¹tkowy w œrodku lewego tylnego ko³a
	//TODO: przerobiæ na dwa fory, mno¿¹c y

	wheels.insert(wheels.end(), { lfWheel,rfWheel,lmWheel,rmWheel,lrWheel,rrWheel });
	//TODO: znalezc lepszy pomys³ na to ^

	for (auto wheel : wheels)
	{
		wheel.setColor(1, 0, 0);
		wheel.draw();
	}

	Walec fAxle(xpos,ypos+ylen,zpos,axleRadius,axleHeight);
	Walec mAxle(xpos, ypos + ylen/2, zpos, axleRadius, axleHeight);
	Walec rAxle(xpos, ypos, zpos, axleRadius, axleHeight);


	//TODO: przerobiæ na dwa fory, mno¿¹c y

	axles.insert(axles.end(), { fAxle,mAxle,rAxle });
	//TODO: znalezc lepszy pomys³ na to ^

	for (auto axle : axles)
	{
		axle.setColor(0, 0, 1);
		axle.draw();
	}

	Szescian platform(xpos, ypos, zpos+platformEvelation, xlen, ylen, zpos + platformThickness);
	platform.setColor(0, 1, 0);
	platform.draw();
}

void Lazik::setParams()
{
	//TODO: parametryzacja i opis

	wheelRadius = 8;
	wheelHeight = 10;
	axleRadius=wheelHeight/5;
	axleHeight=xlen;
	platformEvelation = 10;
	platformThickness = 5;

}
