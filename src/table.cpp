// This file contains definitions for the components of the table

#include <GL/gl.h>
#include <GL/glut.h>

#include "table.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_table_top() {
	int table_top = glGenLists(1);
	int table_top_texture = LoadTexture("tex/wood.bmp");
	glNewList(table_top, GL_COMPILE);
		glColor3ub(167,123,204);
		glPushMatrix();
			// glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		 //    glEnable(GL_TEXTURE_GEN_T);
		 //    glBindTexture(GL_TEXTURE_2D, table_top_texture);
			glScalef(4,0.25,2);
			glutSolidCube(1);
			// glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		 //    glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();
	glEndList();
	return table_top;
}

int define_table_leg() {
	int table_leg = glGenLists(1);
	glNewList(table_leg, GL_COMPILE);
		glPushMatrix();
			glColor3ub(50,100,50);
			glScalef(0.125,2,0.125);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return table_leg;
}