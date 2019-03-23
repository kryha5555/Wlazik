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

	GLfloat wheelRadius; // promien ko³a
	GLfloat wheelHeight; // wysokosc (szerokosc) kola
	std::vector<Walec> wheels;

	GLfloat axleRadius; // promien osi
	GLfloat axleHeight; // wysokosc (szerokosc) osi
	std::vector<Walec> axles;

	GLfloat platformEvelation; // podniesienie platformy nad poziom osi
	GLfloat platformThickness; // grubosc platformy

};

