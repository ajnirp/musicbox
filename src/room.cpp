// This file contains definitions for the components of the room

#include <GL/gl.h>
#include <GL/glut.h>

#include "room.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_floor() {
	int room_floor = glGenLists(1);
	glNewList(room_floor, GL_COMPILE);
		glPushMatrix();
			glBegin(GL_QUADS);
				// glVertex3f(-5,-3,3);
				// glVertex3f(5,-3,3);
				// glVertex3f(5,-3,-3);
				// glVertex3f(5,-3,-3);
			glEnd();
		glPopMatrix();
	glEndList();
	return room_floor;
}

int define_side_wall() {
	int room_side_wall = glGenLists(1);
	glNewList(room_side_wall, GL_COMPILE);
		glPushMatrix();
			glBegin(GL_QUADS);
				// glVertex3f();
				// glVertex3f();
				// glVertex3f();
				// glVertex3f();
			glEnd();
		glPopMatrix();
	glEndList();
	return room_side_wall;
}

int define_facing_wall() {

}