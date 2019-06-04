#include "..\include\Szescian.h"


Szescian::Szescian(GLfloat x, GLfloat y, GLfloat z, GLfloat lenx, GLfloat leny, GLfloat lenz, unsigned int tex)
	: Figura(x, y, z)
	, xlen{ lenx }
	, ylen{ leny }
	, zlen{ lenz }
	, tex{ tex }
{
}

Szescian::~Szescian()
{
}

void Szescian::draw()
{
	//podany punkt jest jednym z rogow
	GLfloat sa[3] = { xpos, ypos, zpos };
	GLfloat sb[3] = { xpos + xlen, ypos, zpos };
	GLfloat sc[3] = { xpos + xlen, ypos + ylen ,zpos };
	GLfloat sd[3] = { xpos,ypos + ylen, zpos };
	GLfloat se[3] = { xpos,ypos, zpos + zlen };
	GLfloat sf[3] = { xpos + xlen, ypos, zpos + zlen };
	GLfloat sg[3] = { xpos + xlen, ypos + ylen,zpos + zlen };
	GLfloat sh[3] = { xpos,ypos + ylen,zpos + zlen };


	/*
	glPushMatrix();


	rock.setColor(0.89, 0.44, 0.1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tekstury[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	rock.draw();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPopMatrix();

	*/


	glPushMatrix();
	if (tex)
	{
		this->setColor(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Sciany skladowe
	glColor3fv(color);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);
	glVertex3fv(sa);
	glTexCoord2d(0, 1);
	glVertex3fv(sb);
	//glVertex3fv(sc);
	glTexCoord2d(1, 1);
	glVertex3fv(sd);
	glTexCoord2d(1, 0);
	glVertex3fv(sc);
	glEnd();

	//	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);
	glVertex3fv(sb);
	glTexCoord2d(0, 1);
	glVertex3fv(sf);
	//glVertex3fv(sg);
	glTexCoord2d(1, 1);
	glVertex3fv(sc);
	glTexCoord2d(1, 0);
	glVertex3fv(sg);
	glEnd();

	//	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(1, 0);
	glVertex3fv(sf);
	glTexCoord2d(0, 0);
	glVertex3fv(se);
	//glVertex3fv(sh);
	glTexCoord2d(1, 1);
	glVertex3fv(sg);
	glTexCoord2d(0, 1);
	glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);
	glVertex3fv(se);
	glTexCoord2d(0, 1);
	glVertex3fv(sa);
	//glVertex3fv(sd);
	glTexCoord2d(1, 1);
	glVertex3fv(sh);
	glTexCoord2d(1, 0);
	glVertex3fv(sd);
	glEnd();

	//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);
	glVertex3fv(sd);
	glTexCoord2d(0, 1);
	glVertex3fv(sc);
	//glVertex3fv(sg);
	glTexCoord2d(1, 1);
	glVertex3fv(sh);
	glTexCoord2d(1, 0);
	glVertex3fv(sg);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);
	glVertex3fv(sa);
	glTexCoord2d(0, 1);
	glVertex3fv(sb);
	//	glVertex3fv(sf);
	glTexCoord2d(1, 1);
	glVertex3fv(se);
	glTexCoord2d(1, 0);
	glVertex3fv(sf);
	glEnd();

	if(tex) 
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
