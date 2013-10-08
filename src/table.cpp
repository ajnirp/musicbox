#include <GL/glut.h>
#include "table.hpp"

int table;

void define_table() {
	table = glGenLists(1);
	glNewList(table, GL_COMPILE);
		glColor3ub(120,240,50);
		glBegin(GL_QUADS);
			glVertex3f(-5, -3.5, 2);
			glVertex3f(5,-3.5, 2);
			glVertex3f(5, -3.5, -2);
			glVertex3f(-5, -3.5, -2);
		glEnd();
	glEndList();
}

void draw_table() {
	// glPushMatrix();
		glCallList(table);
	// glPopMatrix();
}
