#pragma once
#include <windows.h> 
#include <gl\gl.h>             
#include <gl\glu.h>  
#include <math.h>
class Figura
{
public:
	Figura(GLfloat x, GLfloat y, GLfloat z);
	~Figura();

	void setColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void draw();


	GLfloat xpos, ypos, zpos;
	GLfloat color[3];


};

