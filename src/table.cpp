// This file contains definitions for the components of the table

#include <GL/gl.h>
#include <GL/glut.h>

#include "table.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_table_top() {
	int table_top = glGenLists(1);
	glNewList(table_top, GL_COMPILE);
		glPushMatrix();
			glScalef(3,0.5,1);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return table_top;
}

int define_table_leg() {
	int table_leg = glGenLists(1);
	glNewList(table_leg, GL_COMPILE);
	glEndList();
	return table_leg;
}