#include "..\include\Lazik.h"


Lazik::Lazik(GLfloat x, GLfloat y, GLfloat z)
	: Figura(x, y, z)
{
	setParams();
}

Lazik::~Lazik()
{
}

void Lazik::draw()
{
	// drawing wheels
	// left right; front middle rear
	Walec lfWheel(
		xpos, 
		ypos + ylen,
		zpos, 
		wheelRadius,
		-wheelHeight
	);

	Walec lmWheel(
		xpos, 
		ypos + ylen / 3, 
		zpos, 
		wheelRadius, 
		-wheelHeight
	);
	Walec lrWheel(
		xpos, 
		ypos, 
		zpos, 
		wheelRadius,
		-wheelHeight
	);

	wheels.insert(wheels.end(), { lfWheel,lmWheel,lrWheel });

	Walec rfWheel(
		xpos + xlen + 4 * axleRadius, 
		ypos + ylen, 
		zpos,
		wheelRadius,
		wheelHeight
	);

	Walec rmWheel(
		xpos + xlen + 4 * axleRadius, 
		ypos + ylen / 3,
		zpos, 
		wheelRadius, 
		wheelHeight
	);

	Walec rrWheel(
		xpos + xlen + 4 * axleRadius, 
		ypos, 
		zpos, 
		wheelRadius, 
		wheelHeight
	);


	wheels.insert(wheels.end(), { rfWheel,rmWheel,rrWheel });
	//TODO: znalezc lepszy pomysl na to ^

	for (auto wheel : wheels)
	{
		wheel.setColor(1, 0, 0);
		wheel.draw();
	}

	//drawing wheel axles
	//left right; front top bottom rear
	Walec lfAxle(
		xpos,
		ypos + ylen,
		zpos,
		axleRadius,
		xpos + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2
	);

	Walec ltAxle(
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleRadius,
		xpos + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2
	);

	Walec lbAxle(
		xpos,
		ypos + ylen / 3,
		zpos,
		axleRadius,
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation
	);

	Walec lrAxle(
		xpos,
		ypos,
		zpos,
		axleRadius,
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation
	);

	axles.insert(axles.end(), { lfAxle,ltAxle,lbAxle, lrAxle });

	Walec rfAxle(
		xpos + xlen + 4 * axleRadius,
		ypos + ylen,
		zpos,
		axleRadius,
		xpos + +xlen + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2
	);

	Walec rtAxle(
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleRadius,
		xpos + xlen + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2
	);

	Walec rbAxle(xpos + xlen + 4 * axleRadius,
		ypos + ylen / 3,
		zpos,
		axleRadius,
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation
	);

	Walec rrAxle(
		xpos + xlen + 4 * axleRadius,
		ypos,
		zpos,
		axleRadius,
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation
	);

	axles.insert(axles.end(), { rfAxle,rtAxle,rbAxle,rrAxle });
	//TODO: znalezc lepszy pomysl na to ^

	for (auto axle : axles)
	{
		axle.setColor(0, 0, 1);
		axle.draw();
	}

	//drawing platform
	Szescian platform(
		xpos + 2 * axleRadius, 
		ypos, 
		zpos + platformEvelation, 
		xlen, 
		ylen, 
		platformThickness
	);

	platform.setColor(0, 1, 0);
	platform.draw();

	//drawing camera
	Walec cameraStand(
		xpos + xlen + 2 * axleRadius - 1.5*cameraStandRadius,  // xpos + xlen + 2 * axleRadius puts center of the base in right-front corner
		ypos + ylen - 1.5*cameraStandRadius, // ypos + ylen, as above
		zpos + platformEvelation + platformThickness, 
		cameraStandRadius, 
		cameraStandHeight //temporary, parameterized
	);

	cameraStand.setColor(0, 0, 1);
	cameraStand.draw(-90,0,1,0); 

	Szescian cameraBox(
		xpos + xlen + 2 * axleRadius - 1.5*cameraStandRadius-cameraxlen/2,
		ypos + ylen - 1.5*cameraStandRadius-cameraylen /2,
		zpos + platformEvelation + platformThickness+cameraStandHeight,
		cameraxlen,
		cameraylen,
		camerazlen
	);
	
	cameraBox.setColor(1, 0, 0);
	cameraBox.draw();

}

void Lazik::setParams()
{
	//TODO: parametryzacja i opis

	wheelRadius = 8;
	wheelHeight = 10;

	axleRadius = wheelHeight / 5;
	axleHeight = xlen + 4 * axleRadius; //unused

	xlen = 6 * wheelRadius;
	ylen = 8 * wheelRadius;
	zlen = wheelRadius; // unused
	platformEvelation = 15;
	platformThickness = 10; // same as zlen?

	cameraStandRadius = 1.5*axleRadius;
	cameraStandHeight = 3 * cameraStandRadius;
	cameraxlen=ylen/3;
	cameraylen=xlen/3;
	camerazlen=platformThickness/3;
}
