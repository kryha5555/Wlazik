#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>  
#include "Figura.h"

class Walec : public Figura
{
public:
	Walec(GLfloat x=0, GLfloat y=0, GLfloat z=0, GLfloat r=0, GLfloat h=0 );
	~Walec();

	void draw();
private:

	GLfloat rlen;
	GLfloat hlen;
};

