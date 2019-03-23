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

	GLfloat wheelRadius; // promieñ ko³a
	GLfloat wheelHeight; // wysokoœc (szerokoœæ) ko³a
	std::vector<Walec> wheels;

	GLfloat axleRadius; // promieñ osi
	GLfloat axleHeight; // wysokoœæ (szerokoœæ) osi
	std::vector<Walec> axles;

	GLfloat platformEvelation; // podniesienie platformy nad poziom osi
	GLfloat platformThickness; // gruboœæ platformy

};

