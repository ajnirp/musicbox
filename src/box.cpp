#include <GL/glut.h>
#include "box.hpp"

int define_base_and_walls() {
	int base_and_walls = glGenLists(1);
	glNewList(base_and_walls, GL_COMPILE);
		glPushMatrix();
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
			glTranslatef(-1.5,-3.5,-2);
			glScalef(3,3,3);
			glColor3ub(140,60,90);
			glColor3i(1,1,1);
			// Front wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(1,0,0);
				glVertex3f(1,0.5,0);
				glVertex3f(0,0.5,0);
			glEnd();
			glColor3ub(100,120,100);
			// Right wall
			glBegin(GL_QUADS);
				glVertex3f(1,0,0);
				glVertex3f(1,0,-1);
				glVertex3f(1,0.5,-1);
				glVertex3f(1,0.5,0);
			glEnd();
			// Left wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0,0.5,0);
				glVertex3f(0,0.5,-1);
				glVertex3f(0,0,-1);
			glEnd();
			glColor3ub(100,170,50);
			// Back wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,-1);
				glVertex3f(1,0,-1);
				glVertex3f(1,0.5,-1);
				glVertex3f(0,0.5,-1);
			glEnd();
			glColor3ub(200,170,50);

			// Base
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(1,0,0);
				glVertex3f(1,0,-1);
				glVertex3f(0,0,-1);
			glEnd();
		glPopMatrix();
	glEndList();
	return base_and_walls;
}

int define_lid() {
	int lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
		glPushMatrix();
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
			glTranslatef(-1.5,-2,-2); // at y = -2 the lid exactly covers the box
			glScalef(3,3,3);
			glColor3ub(140,60,90);
			glColor3i(1,1,1);
			// Front wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(1,0,0);
				glVertex3f(1,0.05,0);
				glVertex3f(0,0.05,0);
			glEnd();
			glColor3ub(100,20,100);
			// Right wall
			glBegin(GL_QUADS);
				glVertex3f(1,0,0);
				glVertex3f(1,0,-1);
				glVertex3f(1,0.05,-1);
				glVertex3f(1,0.05,0);
			glEnd();
			// Left wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0,0.05,0);
				glVertex3f(0,0.05,-1);
				glVertex3f(0,0,-1);
			glEnd();
			// Back wall
			glBegin(GL_QUADS);
				glVertex3f(0,0,-1);
				glVertex3f(1,0,-1);
				glVertex3f(1,0.05,-1);
				glVertex3f(0,0.05,-1);
			glEnd();
			glColor3ub(130,140,50);
			// Top
			glBegin(GL_QUADS);
				glVertex3f(0,0.05,0);
				glVertex3f(1,0.05,0);
				glVertex3f(1,0.05,-1);
				glVertex3f(0,0.05,-1);
			glEnd();
		glPopMatrix();
	glEndList();
	return lid;
}

void draw_box(double lid_degrees, double box_degrees) {
	int base_and_walls = define_base_and_walls();
	int lid = define_lid();

	glPushMatrix();
		glTranslatef(0, 0, -2);
		glRotatef(box_degrees, 0, 1, 0);
		glTranslatef(0, 0, 2);
		// draw the lid
		glPushMatrix();
			glTranslatef(0, -2, -5);
			glRotatef(lid_degrees, 1, 0, 0);
			glTranslatef(0, 2, 5);
			glCallList(lid);
		glPopMatrix();
		// draw the base and walls
		glCallList(base_and_walls);
	glPopMatrix();
}