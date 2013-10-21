// This file contains definitions for the components of the room

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

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
	GLuint texture_door = LoadTexture("tex/wood.bmp");
	int door = glGenLists(1);
	glNewList(door, GL_COMPILE);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, texture_door);
			// glColor3ub(40,50,60);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(1,-3,3);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(3,-3,3);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(3,0,3);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(1,0,3);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glEndList();
	return door;
}

// Table

int define_table_top() {
	int table_top = glGenLists(1);
	// int table_top_texture = LoadTexture("tex/wood.bmp");
	glNewList(table_top, GL_COMPILE);
		glColor3ub(155,69,39);
		// glColor3ub(192,64,0);
		glPushMatrix();
			glScalef(4,0.25,2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return table_top;
}

int define_table_leg() {
	int table_leg = glGenLists(1);
	glNewList(table_leg, GL_COMPILE);
		glPushMatrix();
		glColor3ub(155,69,39);
			glScalef(0.125,2,0.125);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return table_leg;
}

// one_legged table

int define_one_legged_table_top() {
	int one_legged_table_texture = LoadTexture("tex/wood.bmp");
	int one_legged_table_top = glGenLists(1);
	glNewList(one_legged_table_top, GL_COMPILE);
		// define_cylinder(1.5,1.5,0.1,one_legged_table_texture);
		glPushMatrix();
			glColor3ub(129,113,95);
			glScalef(2,0.1,2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return one_legged_table_top;
}

int define_one_legged_table_leg() {
	int one_legged_table_texture = LoadTexture("tex/wood.bmp");
	int one_legged_table_leg = glGenLists(1);
	glNewList(one_legged_table_leg, GL_COMPILE);
		// define_cylinder(0.3,0.3,1.5,one_legged_table_texture);
		glPushMatrix();
			glScalef(0.3,1.5,0.3);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return one_legged_table_leg;
}

int define_one_legged_table_base() {
	int one_legged_table_texture = LoadTexture("tex/wood.bmp");
	int one_legged_table_base = glGenLists(1);
	glNewList(one_legged_table_base, GL_COMPILE);
		// define_cylinder(0.7,0.7,0.1,one_legged_table_texture);
		glPushMatrix();
			glScalef(1.2,0.1,1.2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return one_legged_table_base;
}

// Chair

int define_chair_seat() {
	int chair_seat = glGenLists(1);
	glNewList(chair_seat, GL_COMPILE);
		glColor3ub(150,120,90);
		glPushMatrix();
			glScalef(0.7,0.1,0.7);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return chair_seat;
}

int define_chair_leg() {
	int chair_leg = glGenLists(1);
	glNewList(chair_leg, GL_COMPILE);
		glColor3ub(150,120,60);
		glPushMatrix();
			glScalef(0.1,0.7,0.1);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return chair_leg;
}

int define_chair_back() {
	int chair_back = glGenLists(1);
	glNewList(chair_back, GL_COMPILE);
		glColor3ub(150,120,60);
		glPushMatrix();
			glScalef(0.7,1.2,0.1);
			glutSolidCube(1);
		glPopMatrix();	
	glEndList();
	return chair_back;
}

// Lamp

int define_lamp_stand() {
	int lamp_stand = glGenLists(1);
	glNewList(lamp_stand, GL_COMPILE);
		glColor3ub(50,50,50);
		glPushMatrix();
			define_cylinder(0.05,0.05,3,-1);
		glPopMatrix();
	glEndList();
	return lamp_stand;
}

int define_lamp_head() {
	int lamp_head = glGenLists(1);
	// int texture_lamp_head = LoadTexture("tex/lamp-head.bmp");
	glNewList(lamp_head, GL_COMPILE);
		glColor3ub(255,0,0);
		glPushMatrix();
			define_cylinder(0.3,0.6,0.8,-1);
		glPopMatrix();
	glEndList();
	return lamp_head;
}

int define_lamp_base() {
	int lamp_base = glGenLists(1);
	glNewList(lamp_base, GL_COMPILE);
		glColor3ub(50,50,50);
		glPushMatrix();
			// define_cylinder(0.3,0.3,0.1,-1);
		glScalef(0.6,0.1,0.6);
		glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return lamp_base;
}

// Stool

int define_stool_seat() {
	int texture_stool_seat = LoadTexture("tex/wood.bmp");
	int stool_seat = glGenLists(1);
	glNewList(stool_seat, GL_COMPILE);
		glPushMatrix();
			define_cylinder(0.7,0.7,0.1,texture_stool_seat);
			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texture_stool_seat);

				glTranslatef(0,0.05,0);
				glRotatef(90,1,0,0);
				glBegin(GL_POLYGON); // base of the stool
				for (int i = 0 ; i < 360 ; i++) {
					if (i==0) glTexCoord2f(0,0);
					if (i==90) glTexCoord2f(0,1);
					if (i==180) glTexCoord2f(1,1);
					if (i==270) glTexCoord2f(1,0);
					glVertex3f(0.7*cos(i),0.7*sin(i),0);
				}

				glDisable(GL_TEXTURE_2D);
			glEnd();
			glPopMatrix();
		glPopMatrix();
	glEndList();
	return stool_seat;
}

int define_stool_leg() {
	int texture_stool_leg = LoadTexture("tex/wood.bmp");
	int stool_leg = glGenLists(1);
	glNewList(stool_leg, GL_COMPILE);
		glPushMatrix();
			define_cylinder(0.05,0.05,1,texture_stool_leg);
		glPopMatrix();
	glEndList();
	return stool_leg;
}

// Wall Light

int define_wall_light_base() {
	int wall_light_base = glGenLists(1);
	glNewList(wall_light_base, GL_COMPILE);
		glColor3ub(90,90,90);
		glPushMatrix();
			glScalef(0.4,0.4,0.1);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return wall_light_base;
}

int define_wall_light_neck() {
	int wall_light_neck = glGenLists(1);
	glNewList(wall_light_neck, GL_COMPILE);
		glColor3ub(90,90,90);
		glPushMatrix();
			glScalef(0.05,0.05,0.4);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return wall_light_neck;
}

int define_wall_light_head() {
	int wall_light_head = glGenLists(1);
	glNewList(wall_light_head, GL_COMPILE);
		glPushMatrix();
			define_cylinder(0.2,0.2,0.5,-1);
		glPopMatrix();
	glEndList();
	return wall_light_head;
}