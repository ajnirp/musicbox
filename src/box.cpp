// This file contains definitions for the components of the box

// #include <GLUT/glut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "box.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_base_and_walls() {
	int base_and_walls = glGenLists(1);
	
	GLuint texture_base_and_walls = LoadTexture("tex/wood.bmp");
	glNewList(base_and_walls, GL_COMPILE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture_base_and_walls);

		glTranslatef(-1.5,-3.5,-2);
		glScalef(3,3,3);
		glColor3ub(140,60,200);
		// Front wall
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
		glTexCoord2f(0.0, 1.0);glVertex3f(1,0,0);
		glTexCoord2f(1.0, 1.0);glVertex3f(1,0.5,0);
		glTexCoord2f(1.0, 0.0);glVertex3f(0,0.5,0);
		glEnd();
		glColor3ub(100,120,100);
		// Right wall
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(1,0,0);
		glTexCoord2f(0.0, 1.0);glVertex3f(1,0,-1);
		glTexCoord2f(1.0, 1.0);glVertex3f(1,0.5,-1);
		glTexCoord2f(1.0, 0.0);glVertex3f(1,0.5,0);
		glEnd();
		// Left wall
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
		glTexCoord2f(0.0, 1.0);glVertex3f(0,0.5,0);
		glTexCoord2f(1.0, 1.0);glVertex3f(0,0.5,-1);
		glTexCoord2f(1.0, 0.0);glVertex3f(0,0,-1);
		glEnd();
		glColor3ub(100,170,50);
		// Back wall
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(0,0,-1);
		glTexCoord2f(0.0, 1.0);glVertex3f(1,0,-1);
		glTexCoord2f(1.0, 1.0);glVertex3f(1,0.5,-1);
		glTexCoord2f(1.0, 0.0);glVertex3f(0,0.5,-1);
		glEnd();
		glColor3ub(200,170,50);

		// Base
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
		glTexCoord2f(0.0, 1.0);glVertex3f(1,0,0);
		glTexCoord2f(1.0, 1.0);glVertex3f(1,0,-1);
		glTexCoord2f(1.0, 0.0);glVertex3f(0,0,-1);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glEndList();
	
	return base_and_walls;
}

int define_lid() {
	int lid = glGenLists(1);
	GLuint texture_lid = LoadTexture("tex/wood2.bmp");
	glNewList(lid, GL_COMPILE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture_lid);

		glTranslatef(-1.5,-2,-2); // at y = -2 the lid exactly covers the box
		glScalef(3,3,3);
		glColor3ub(220,70,100);
		// glColor3i(1,1,1);
		// Front wall
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
			glTexCoord2f(0.0, 1.0);glVertex3f(1,0,0);
			glTexCoord2f(1.0, 1.0);glVertex3f(1,0.05,0);
			glTexCoord2f(1.0, 0.0);glVertex3f(0,0.05,0);
		glEnd();
		glColor3ub(100,20,100);
		// Right wall
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(1,0,0);
			glTexCoord2f(0.0, 1.0);glVertex3f(1,0,-1);
			glTexCoord2f(1.0, 1.0);glVertex3f(1,0.05,-1);
			glTexCoord2f(1.0, 0.0);glVertex3f(1,0.05,0);
		glEnd();
		// Left wall
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,0);
			glTexCoord2f(0.0, 1.0);glVertex3f(0,0.05,0);
			glTexCoord2f(1.0, 1.0);glVertex3f(0,0.05,-1);
			glTexCoord2f(1.0, 0.0);glVertex3f(0,0,-1);
		glEnd();
		// Back wall
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,-1);
			glTexCoord2f(0.0, 1.0);glVertex3f(1,0,-1);
			glTexCoord2f(1.0, 1.0);glVertex3f(1,0.05,-1);
			glTexCoord2f(1.0, 0.0);glVertex3f(0,0.05,-1);
		glEnd();
		glColor3ub(130,140,50);
		// Top
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0.05,0);
			glTexCoord2f(0.0, 1.0);glVertex3f(1,0.05,0);
			glTexCoord2f(1.0, 1.0);glVertex3f(1,0.05,-1);
			glTexCoord2f(1.0, 0.0);glVertex3f(0,0.05,-1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return lid;
}


