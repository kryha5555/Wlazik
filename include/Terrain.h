#pragma once
#define NOMINMAX
#include <windows.h>  
#include <gl\gl.h>             
#include <gl\glu.h>  
#include "OBJ_Loader.h"
#include "Figura.h"
#include <algorithm>


class Terrain : public Figura
{
public:
	Terrain(const char *filename, GLfloat x, GLfloat y, GLfloat z);
	~Terrain();

	void draw();
	GLfloat *getBB();

private:
	const char *filename;
	GLfloat BB[4] = { 0,0,0,0 };// X,Y,x,y
	GLfloat max4(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
	GLfloat min4(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
//	GLfloat xpos, ypos, zpos;
};

