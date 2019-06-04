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
		-wheelHeight,
		wheelTex
	);

	Walec lmWheel(
		xpos,
		ypos + ylen / 3,
		zpos,
		wheelRadius,
		-wheelHeight,
		wheelTex
	);
	Walec lrWheel(
		xpos,
		ypos,
		zpos,
		wheelRadius,
		-wheelHeight,
		wheelTex
	);

	wheels.insert(wheels.end(), { lfWheel,lmWheel,lrWheel });

	Walec rfWheel(
		xpos + xlen + 4 * axleRadius,
		ypos + ylen,
		zpos,
		wheelRadius,
		wheelHeight,
		wheelTex
	);

	Walec rmWheel(
		xpos + xlen + 4 * axleRadius,
		ypos + ylen / 3,
		zpos,
		wheelRadius,
		wheelHeight,
		wheelTex
	);

	Walec rrWheel(
		xpos + xlen + 4 * axleRadius,
		ypos,
		zpos,
		wheelRadius,
		wheelHeight,
		wheelTex
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
		zpos + platformEvelation + platformThickness / 2,
		axleTex
	);

	Walec ltAxle(
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleRadius,
		xpos + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2,
		axleTex
	);

	Walec lbAxle(
		xpos,
		ypos + ylen / 3,
		zpos,
		axleRadius,
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleTex
	);

	Walec lrAxle(
		xpos,
		ypos,
		zpos,
		axleRadius,
		xpos + axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleTex
	);

	axles.insert(axles.end(), { lfAxle,ltAxle,lbAxle, lrAxle });

	Walec rfAxle(
		xpos + xlen + 4 * axleRadius,
		ypos + ylen,
		zpos,
		axleRadius,
		xpos + +xlen + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2,
		axleTex
	);

	Walec rtAxle(
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleRadius,
		xpos + xlen + 2 * axleRadius,
		ypos + (2.f / 3.f)*ylen,
		zpos + platformEvelation + platformThickness / 2,
		axleTex
	);

	Walec rbAxle(xpos + xlen + 4 * axleRadius,
		ypos + ylen / 3,
		zpos,
		axleRadius,
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleTex
	);

	Walec rrAxle(
		xpos + xlen + 4 * axleRadius,
		ypos,
		zpos,
		axleRadius,
		xpos + xlen + 3 * axleRadius,
		ypos + ylen / 6,
		zpos + (2.f / 3.f)*platformEvelation,
		axleTex
	);

	axles.insert(axles.end(), { rfAxle,rtAxle,rbAxle,rrAxle });
	//TODO: znalezc lepszy pomysl na to ^

	for (auto axle : axles)
	{
		axle.setColor(0, 0, 1);
		axle.draw();
	}



	//drawing camera
	Walec cameraStand(
		xpos + xlen + 2 * axleRadius - 1.5*cameraStandRadius,  // xpos + xlen + 2 * axleRadius puts center of the base in right-front corner
		ypos + ylen - 1.5*cameraStandRadius, // ypos + ylen, as above
		zpos + platformEvelation + platformThickness,
		cameraStandRadius,
		cameraStandHeight, //temporary, parameterized,,
		axleTex
	);

	cameraStand.setColor(1, 0, 1);
	cameraStand.draw(-90, 0, 1, 0);

	Szescian cameraBox(
		xpos + xlen + 2 * axleRadius - 1.5*cameraStandRadius - cameraxlen / 2,
		ypos + ylen - 1.5*cameraStandRadius - cameraylen / 2,
		zpos + platformEvelation + platformThickness + cameraStandHeight,
		cameraxlen,
		cameraylen,
		camerazlen
	);

	cameraBox.setColor(1, 0, 0);
	cameraBox.draw();

	//drawing radio
	Walec radioStand(
		xpos + xlen + 2 * axleRadius - 1.5*radioStandRadius,
		ypos + 1.5*cameraStandRadius,
		zpos + platformEvelation + platformThickness,
		radioStandRadius,
		radioStandHeight,
		axleTex
	);

	radioStand.setColor(1, 0, 1);
	radioStand.draw(-90, 0, 1, 0);

	Walec radioTop(
		xpos + xlen + 2 * axleRadius - 1.5*radioStandRadius,
		ypos + 1.5*cameraStandRadius,
		zpos + platformEvelation + platformThickness + radioStandHeight,
		radioTopRadius,
		radioTopHeight
	);

	radioTop.setColor(1, 0, 1);
	radioTop.draw(-90, 0, 1, 0);

	//drawing flag
	Walec flagPole(
		xpos + 2 * axleRadius + 5 * flagPoleRadius,
		ypos + 5 * flagPoleRadius,
		zpos + platformEvelation + platformThickness,
		flagPoleRadius,
		flagPoleHeight,
		axleTex
	);

	flagPole.setColor(1, 0, 1);
	flagPole.draw(-90, 0, 1, 0);

	Szescian flag(
		xpos + 2 * axleRadius + 5 * flagPoleRadius,
		ypos + 5 * flagPoleRadius + flagylen / 2,
		zpos + platformEvelation + platformThickness + flagPoleHeight,
		-flagxlen,
		-flagylen,
		-flagzlen
	);
	flag.setColor(0, 0, 0);
	flag.draw();

	//drawing platform top
	Szescian platformTopBack(
		xpos + 2 * axleRadius,
		ypos + 5 * radioStandRadius,
		zpos + platformEvelation + platformThickness,
		xlen,
		platformTopxlen*(2.f / 3.f),
		platformTopHeight
	);

	platformTopBack.setColor(0.22f, 0.72f, 0.80f);
	platformTopBack.draw();

	TriangularPrism platformTopFront(
		xpos + xlen + 2 * axleRadius,
		ypos + 5 * radioStandRadius + platformTopxlen * (2.f / 3.f),
		zpos + platformEvelation + platformThickness,

		platformTopHeight, // w z po rotacji

		platformTopxlen*(1.f / 3.f),  // w y po rotacji
		xlen // w x po rotacji

	);

	platformTopFront.setColor(0.22f, 0.72f, 0.80f);

	platformTopFront.draw(-90, 0, 1, 0);





	//drawing platform
	Szescian platform(
		xpos + 2 * axleRadius,
		ypos,
		zpos + platformEvelation,
		xlen,
		ylen,
		platformThickness,
		szescianTex
	);

	platform.setColor(0, 1, 0);
	platform.draw();

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
	cameraxlen = ylen / 3;
	cameraylen = xlen / 3;
	camerazlen = platformThickness / 3;

	radioStandRadius = axleRadius;
	radioStandHeight = 8 * radioStandRadius;
	radioTopRadius = radioStandRadius * 2;
	radioTopHeight = radioStandHeight / 2;

	flagPoleRadius = 0.5f;
	flagPoleHeight = 3 * cameraStandHeight;
	flagxlen = 20;
	flagylen = 0.5f;
	flagzlen = 10;

	platformTopxlen = ylen - cameraxlen;
	platformTopHeight = 1.5*platformThickness;
}

std::vector<GLfloat> Lazik::getPos()
{
	std::vector<GLfloat> pos;
	pos.push_back(xpos + 2 * axleRadius + xlen / 2);
	pos.push_back(ypos + ylen / 2);
	pos.push_back(zpos + platformEvelation + platformThickness + platformTopHeight);

	return pos;
}

GLfloat Lazik::getAxleTrack()
{
	return xlen + 4 * axleRadius;
}

GLfloat Lazik::getRadius()
{
	return GLfloat();
}

void Lazik::setSzescianTex(unsigned int tex)
{
	szescianTex = tex;
}

void Lazik::setWheelTex(unsigned int tex)
{
	wheelTex = tex;
}

void Lazik::setAxleTex(unsigned int tex)
{
	axleTex = tex;
}

GLfloat * Lazik::getBB()
{
	BB[0] = xpos + ylen + wheelRadius;
	BB[1] = ypos + ylen + wheelRadius;
	BB[2] = xpos - wheelRadius;
	BB[3] = ypos - wheelRadius;



	return BB;
}

bool Lazik::isColliding(GLfloat * obstacleBB)
{
	//return !(BB[0] < obstacleBB[2] || obstacleBB[0] < BB[2] || BB[1] < obstacleBB[3] || obstacleBB[1] < BB[3]);
	return !((BB[0] < obstacleBB[2] || obstacleBB[0] < BB[2])&& (BB[1] < obstacleBB[3] || obstacleBB[1] < BB[3]));
}

