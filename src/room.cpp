// This file contains definitions for the components of the room

#include <GL/gl.h>
#include <GL/glut.h>

#include "room.hpp"
#include "shapes.hpp"
#include "texture.hpp"

// Room walls

int define_horizontal_wall(int y) {
	GLuint texture_walls = LoadTexture("tex/room-cropped.bmp");
	int room_floor = glGenLists(1);
	glNewList(room_floor, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(-5,y,3);
				glTexCoord2f(0.0, 1.0);glVertex3f(5,y,3);
				glTexCoord2f(1.0, 1.0);glVertex3f(5,y,-3);
				glTexCoord2f(1.0, 0.0);glVertex3f(-5,y,-3);
			glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_floor;
}

int define_side_wall(int x) {
	GLuint texture_walls = LoadTexture("tex/room-cropped.bmp");
	int room_side_wall = glGenLists(1);
	glNewList(room_side_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(x,-3,3);
				glTexCoord2f(0.0, 1.0);glVertex3f(x,-3,-3);
				glTexCoord2f(1.0, 1.0);glVertex3f(x,4,-3);
				glTexCoord2f(1.0, 0.0);glVertex3f(x,4,3);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_side_wall;
}

int define_back_wall() {
	GLuint texture_walls = LoadTexture("tex/room-cropped.bmp");
	int room_facing_wall = glGenLists(1);
	glNewList(room_facing_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(-5,-3,-3);
				glTexCoord2f(0.0, 1.0);glVertex3f(5,-3,-3);
				glTexCoord2f(1.0, 1.0);glVertex3f(5,4,-3);
				glTexCoord2f(1.0, 0.0);glVertex3f(-5,4,-3);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_facing_wall;
}

int define_front_wall() {
	GLuint texture_walls = LoadTexture("tex/room-cropped.bmp");
	int room_facing_wall = glGenLists(1);
	glNewList(room_facing_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);glVertex3f(-5,-3,3);
			glTexCoord2f(0.6, 0.0);glVertex3f(1,-3,3);
			glTexCoord2f(0.6, 1.0);glVertex3f(1,4,3);
			glTexCoord2f(0.0, 1.0);glVertex3f(-5,4,3);

			glTexCoord2f(0.6, 0.42);glVertex3f(1,0,3);
			glTexCoord2f(0.8, 0.42);glVertex3f(3,0,3);
			glTexCoord2f(0.8, 1.0);glVertex3f(3,4,3);
			glTexCoord2f(0.6, 1.0);glVertex3f(1,4,3);

			glTexCoord2f(0.8, 0.0);glVertex3f(3,-3,3);
			glTexCoord2f(1.0, 0.0);glVertex3f(5,-3,3);
			glTexCoord2f(1.0, 1.0);glVertex3f(5,4,3);
			glTexCoord2f(0.8, 1.0);glVertex3f(3,4,3);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_facing_wall;
}

int define_door() {
	GLuint texture_door = LoadTexture("tex/plank.bmp");
	int door = glGenLists(1);
	glNewList(door, GL_COMPILE);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, texture_door);
			// glTranslatef(1,0,3.001);
			// glRotatef(door_angle,0,1,0);
			// glTranslatef(-1,0,-3.001);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);glVertex3f(1,-3,3.001);
				glTexCoord2f(0.0, 1.0);glVertex3f(3,-3,3.001);
				glTexCoord2f(1.0, 1.0);glVertex3f(3,0,3.001);
				glTexCoord2f(1.0, 0.0);glVertex3f(1,0,3.001);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glEndList();
	return door;
}

// Table

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