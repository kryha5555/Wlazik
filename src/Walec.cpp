#include "..\include\Walec.h"


Walec::Walec(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat h, unsigned int tex)
	: Figura(x, y, z)
	, rlen{ r }
	, hlen{ h }
	, xtpos{ x + h }
	, ytpos{ y }
	, ztpos{ z }
	, tex{ tex }
{
}

Walec::Walec(GLfloat xb, GLfloat yb, GLfloat zb, GLfloat r_, GLfloat xt, GLfloat yt, GLfloat zt, unsigned int tex)
	: Figura(xb, yb, zb)
	, rlen{ r_ }
	, xtpos{ xt }
	, ytpos{ yt }
	, ztpos{ zt }
	, tex{ tex }
{
}

Walec::~Walec()
{
}

void Walec::draw(GLfloat rotdeg, GLfloat rotx, GLfloat roty, GLfloat rotz)
{
	//podany punkt jest srodkiem jednej z podstaw

	GLfloat alpha,ty,tz , y_, z_, PI = 3.14;
	int it = 0;

	glPushMatrix();

	if (tex)
	{
		this->setColor(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	if (rotdeg)
	{
		glTranslatef(xpos, ypos, zpos);
		glRotatef(rotdeg, rotx, roty, rotz);
		glTranslatef(-xpos, -ypos, -zpos);
	}

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(color);

	glVertex3d(xpos, ypos, zpos);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		y_ = ypos + rlen * sin(alpha);
		z_ = zpos + rlen * cos(alpha);
		ty = (y_ / rlen + 1)*0.5;
		tz = (z_ / rlen + 1)*0.5;
		glTexCoord2d(ty, tz);
		glVertex3d(xpos, y_, z_);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		
		y_ = ypos + rlen * sin(alpha);
		z_ = zpos + rlen * cos(alpha);
		if(it%2)
			glTexCoord2d(0, 0);
		else
			glTexCoord2d(1, 0);
		glVertex3d(xpos, y_, z_);

		//glVertex3d(xtpos, y_, z_);

		y_ = ytpos + rlen * sin(alpha);
		z_ = ztpos + rlen * cos(alpha);
		//glVertex3d(xpos, y_, z_);
		if (it % 2)
			glTexCoord2d(0, 1);
		else
			glTexCoord2d(1, 1);

		glVertex3d(xtpos, y_, z_);
		it++;

	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(xtpos, ytpos, ztpos);
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		y_ = ytpos + rlen * sin(alpha);
		z_ = ztpos + rlen * cos(alpha);
		ty = (y_ / rlen + 1)*0.5;
		tz = (z_ / rlen + 1)*0.5;
		glTexCoord2d(ty, tz);
		glVertex3d(xtpos, y_, z_);
	}
	glEnd();

	if (tex)
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

