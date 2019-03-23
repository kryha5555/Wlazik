#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>  
#include "Figura.h"

class Walec : public Figura
{
public:
	Walec(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat h );
	Walec(GLfloat xb, GLfloat yb, GLfloat zb, GLfloat r, GLfloat xt, GLfloat yt, GLfloat zt);
	~Walec();

	void draw();
private:

	GLfloat rlen;
	GLfloat hlen;
	GLfloat xtpos;
	GLfloat ytpos;
	GLfloat ztpos;
};

