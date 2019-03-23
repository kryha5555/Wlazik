#pragma once

#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include "Szescian.h"
#include "Walec.h"
#include <vector>

class Lazik : public Figura
{
public:
	Lazik(GLfloat x, GLfloat y, GLfloat z, GLfloat xlen, GLfloat ylen, GLfloat zlen);
	~Lazik();

	void draw();
	void setParams();

private:
	GLfloat xlen; // width
	GLfloat ylen; // length
	GLfloat zlen; // height

	GLfloat wheelRadius; // promie� ko�a
	GLfloat wheelHeight; // wysoko�c (szeroko��) ko�a
	std::vector<Walec> wheels;

	GLfloat axleRadius; // promie� osi
	GLfloat axleHeight; // wysoko�� (szeroko��) osi
	std::vector<Walec> axles;

	GLfloat platformEvelation; // podniesienie platformy nad poziom osi
	GLfloat platformThickness; // grubo�� platformy

};

