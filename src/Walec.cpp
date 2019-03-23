#include "..\include\Walec.h"


Walec::Walec(GLfloat x, GLfloat y, GLfloat z, GLfloat r_, GLfloat h_)
	: Figura(x, y, z)
	, rlen{ r_ }
	, hlen{ h_ }
{
}

Walec::~Walec()
{
}

void Walec::draw()
{
	//podany punkt jest œrodkiem jednej z podstaw

	GLfloat alpha, y_, z_, PI = 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(color);

	glVertex3d(xpos, ypos, zpos);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		y_ = ypos + rlen * sin(alpha);
		z_ = zpos + rlen * cos(alpha);
		glVertex3d(xpos, y_, z_);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		y_ = ypos + rlen * sin(alpha);
		z_ = zpos + rlen * cos(alpha);
		glVertex3d(xpos, y_, z_);
		glVertex3d(xpos+hlen, y_, z_);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(xpos + hlen, ypos, zpos );
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		y_ = ypos + rlen * sin(alpha);
		z_ = zpos + rlen * cos(alpha);
		glVertex3d(xpos+hlen, y_, z_);
	}
	glEnd();
}
