// This file contains definitions for the components of the room

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#include "room.hpp"
#include "shapes.hpp"
#include "texture.hpp"

// Room walls

int define_floor() {
	GLuint texture_walls = LoadTexture("tex/room-cropped.bmp");
	int room_floor = glGenLists(1);
	glNewList(room_floor, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_walls);

		GLfloat color[] = {1.f,1.f,1.f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);

		glPushMatrix();
			int back_z = -4;
			int front_z = 4;
			int y = -3;
			glBegin(GL_QUADS);
				glNormal3d(0,1,0); // floor normal is upwards
				glTexCoord2f(0.0, 0.0);glVertex3f(-6,y,front_z);
				glTexCoord2f(1.0, 0.0);glVertex3f(9,y,front_z);
				glTexCoord2f(1.0, 1.0);glVertex3f(9,y,back_z);
				glTexCoord2f(0.0, 1.0);glVertex3f(-6,y,back_z);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_floor;
}

int define_ceiling() {
	GLuint texture_walls = LoadTexture("tex/wood4.bmp");
	int room_floor = glGenLists(1);
	glNewList(room_floor, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			int back_z = -4;
			int front_z = 4;
			int y = 6;
			glBegin(GL_QUADS);
				glNormal3d(0,-1,0); // ceiling normal is downwards
				glTexCoord2f(0.0, 0.0);glVertex3f(-6,y,front_z);
				glTexCoord2f(1.0, 0.0);glVertex3f(9,y,front_z);
				glTexCoord2f(1.0, 1.0);glVertex3f(9,y,back_z);
				glTexCoord2f(0.0, 1.0);glVertex3f(-6,y,back_z);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	return room_floor;
}

int define_side_wall(int x, bool left) {
	int texture_walls = LoadTexture("tex/wood4.bmp");
	int room_side_wall = glGenLists(1);
	glNewList(room_side_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			int front_z = 4;
			int back_z = -4;
			glBegin(GL_QUADS);
				if (left) glNormal3d(1,0,0); // left wall normal is along positive x-axis
				else glNormal3d(-1,0,0); // right wall normal is along negative x-axis
				glTexCoord2f(0.0, 0.0);glVertex3f(x,-3,front_z);
				glTexCoord2f(1.0, 0.0);glVertex3f(x,-3,back_z);
				glTexCoord2f(1.0, 1.0);glVertex3f(x,6,back_z);
				glTexCoord2f(0.0, 1.0);glVertex3f(x,6,front_z);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	// glDeleteTextures(1, &texture_walls);
	return room_side_wall;
}

int define_back_wall() {
	GLuint texture_walls = LoadTexture("tex/wood4.bmp");
	int room_facing_wall = glGenLists(1);
	glNewList(room_facing_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		glPushMatrix();
			glBegin(GL_QUADS);
				glNormal3d(0,0,1); // back wall normal is along positive z-axis
				glTexCoord2f(0.0, 0.0);glVertex3f(-6,-3,-4);
				glTexCoord2f(1.0, 0.0);glVertex3f(9,-3,-4);
				glTexCoord2f(1.0, 1.0);glVertex3f(9,6,-4);
				glTexCoord2f(0.0, 1.0);glVertex3f(-6,6,-4);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	// glDeleteTextures(1, &texture_walls);
	return room_facing_wall;
}

int define_front_wall() {
	GLuint texture_walls = LoadTexture("tex/wood4.bmp");
	int room_facing_wall = glGenLists(1);
	glNewList(room_facing_wall, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_walls);
		int z = 4;
		int door_left_x = 2;
		int door_right_x = 5;
		int door_bottom_y = -3;
		int door_top_y = 2;
		glBegin(GL_QUADS);
			glNormal3d(0,0,-1); // front wall normal is along positive z-axis
			glTexCoord2f(0.0, 0.0);glVertex3f(-6,door_bottom_y,z);
			glTexCoord2f(0.6, 0.0);glVertex3f(door_left_x,door_bottom_y,z);
			glTexCoord2f(0.6, 1.0);glVertex3f(door_left_x,6,z);
			glTexCoord2f(0.0, 1.0);glVertex3f(-6,6,z);

			glTexCoord2f(0.6, 0.42);glVertex3f(door_left_x,door_top_y,z);
			glTexCoord2f(0.8, 0.42);glVertex3f(door_right_x,door_top_y,z);
			glTexCoord2f(0.8, 1.0);glVertex3f(door_right_x,6,z);
			glTexCoord2f(0.6, 1.0);glVertex3f(door_left_x,6,z);

			glTexCoord2f(0.8, 0.0);glVertex3f(door_right_x,door_bottom_y,z);
			glTexCoord2f(1.0, 0.0);glVertex3f(9,door_bottom_y,z);
			glTexCoord2f(1.0, 1.0);glVertex3f(9,6,z);
			glTexCoord2f(0.8, 1.0);glVertex3f(door_right_x,6,z);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	// glDeleteTextures(1, &texture_walls);
	return room_facing_wall;
}

int define_door() {
	GLuint texture_door = LoadTexture("tex/wood2.bmp");
	int door = glGenLists(1);
	glNewList(door, GL_COMPILE);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, texture_door);
			// glColor3ub(40,50,60);
			int door_right_x = 5;
			int door_left_x = 2;
			int door_top_y = 2;
			int door_bottom_y = -3;
			int z = 4;
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(door_left_x,door_bottom_y,z);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(door_right_x,door_bottom_y,z);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(door_right_x,door_top_y,z);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(door_left_x,door_top_y,z);
			glEnd();
			glDisable(GL_TEXTURE_2D);

			// door knob
			glBegin(GL_POLYGON); // base of the hat
			glColor3ub(100,100,0);
			for (int i = 0 ; i < 360 ; i++) {
				glVertex3f(2.5+0.2*cos(i),-0.5+0.2*sin(i),z+0.001);
			}
		glEnd();
		glPopMatrix();
	glEndList();
	// glDeleteTextures(1, &texture_door);
	return door;
}

// Table

int define_table_top() {
	int table_top = glGenLists(1);
	glNewList(table_top, GL_COMPILE);
		// glColor3ub(140,82,45);
		GLfloat color[] = {244/255.0f,164/255.0f,96/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {5};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
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
		// glColor3ub(140,82,45);
		GLfloat color[] = {244/255.0f,164/255.0f,96/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			glScalef(0.125,2,0.125);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return table_leg;
}

// one_legged table

int define_one_legged_table_top() {
	int one_legged_table_top = glGenLists(1);
	glNewList(one_legged_table_top, GL_COMPILE);
		GLfloat color[] = {139/255.0f,69/255.0f,19/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {1};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			glScalef(2,0.1,2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return one_legged_table_top;
}

int define_one_legged_table_leg() {
	int one_legged_table_leg = glGenLists(1);
	glNewList(one_legged_table_leg, GL_COMPILE);
		GLfloat color[] = {160/255.0f,82/255.0f,45/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			glScalef(0.3,1.5,0.3);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return one_legged_table_leg;
}
int define_one_legged_table_base() {
	int one_legged_table_base = glGenLists(1);
	glNewList(one_legged_table_base, GL_COMPILE);
		GLfloat color[] = {139/255.0f,69/255.0f,19/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
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
		// glColor3ub(150,120,90);
		GLfloat color[] = {205/255.0f,105/255.0f,0/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
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
		// glColor3ub(150,120,60);
		GLfloat color[] = {205/255.0f,133/255.0f,63/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
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
		// glColor3ub(150,120,60);
		GLfloat color[] = {205/255.0f,133/255.0f,63/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
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
		// glColor3ub(50,50,50);
		GLfloat color[] = {1.0f,1.0f,0.5f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {1};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			define_cylinder(0.05,0.05,3,-1);
		glPopMatrix();
	glEndList();
	return lamp_stand;
}

int define_lamp_head() {
	int lamp_head = glGenLists(1);
	glNewList(lamp_head, GL_COMPILE);
		// glColor3ub(255,0,0);
		GLfloat color[] = {1.f,0.f,0.f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {5};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			define_cylinder(0.3,0.6,0.8,-1);
		glPopMatrix();
	glEndList();
	return lamp_head;
}

int define_lamp_base() {
	int lamp_base = glGenLists(1);
	glNewList(lamp_base, GL_COMPILE);
		// glColor3ub(50,50,50);
		GLfloat color[] = {238/255.0f,221/255.0f,130/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			glScalef(0.6,0.1,0.6);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return lamp_base;
}

int define_lamp_light() {
	int lamp_light = glGenLists(1);
	glNewList(lamp_light, GL_COMPILE);
		glColor3f(1,1,1);
		define_sphere(0.2,-1);
	glEndList();
	return lamp_light;
}

// Stool

int define_stool_seat() {
	// int texture_stool_seat = LoadTexture("tex/metal.bmp");
	int stool_seat = glGenLists(1);
	glNewList(stool_seat, GL_COMPILE);
		GLfloat color[] = {0.5f,0.5f,0.5f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {10};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			define_cylinder(0.7,0.7,0.1,-1);
			glPushMatrix();
				// glEnable(GL_TEXTURE_2D);
				// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				// glBindTexture(GL_TEXTURE_2D, texture_stool_seat);

				glTranslatef(0,0.05,0);
				glRotatef(90,1,0,0);
				glBegin(GL_POLYGON); // base of the stool
					glNormal3d(0,1,0);
					for (int i = 0 ; i < 360 ; i++) {
						// if (i==0) glTexCoord2f(0,0);
						// if (i==90) glTexCoord2f(0,1);
						// if (i==180) glTexCoord2f(1,1);
						// if (i==270) glTexCoord2f(1,0);
						glVertex3f(0.7*cos(i),0.7*sin(i),0);
					}

					// glDisable(GL_TEXTURE_2D);
				glEnd();
			glPopMatrix();
		glPopMatrix();
	glEndList();
	return stool_seat;
}

int define_stool_leg() {
	int stool_leg = glGenLists(1);
	glNewList(stool_leg, GL_COMPILE);
		GLfloat color[] = {0.5f,0.5f,0.5f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {10};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			define_cylinder(0.05,0.05,1,-1);
		glPopMatrix();
	glEndList();
	return stool_leg;
}

// Wall Light

int define_wall_light_base() {
	int wall_light_base = glGenLists(1);
	glNewList(wall_light_base, GL_COMPILE);
		// glColor3ub(90,90,90);
		GLfloat color[] = {200/255.0f,155/255.0f,100/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glPushMatrix();
			glScalef(0.4,0.4,0.1);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
	return wall_light_base;
}

int define_wall_light_neck() {
	GLuint wall_light_neck = glGenLists(1);
	GLuint texture_wall_light_neck = LoadTexture("tex/metal.bmp");
	glNewList(wall_light_neck, GL_COMPILE);
		glPushMatrix();
			glRotatef(90,1,0,0);
			define_cylinder(0.025,0.025,0.4,texture_wall_light_neck);
		glPopMatrix();
	glEndList();
	// glDeleteTextures(1, &texture_wall_light_neck);
	return wall_light_neck;
}

int define_wall_light_head() {
	GLuint texture_wall_light_head = LoadTexture("tex/metal.bmp");
	GLuint wall_light_head = glGenLists(1);
	glNewList(wall_light_head, GL_COMPILE);
		glPushMatrix();
			define_cylinder(0.2,0.2,0.5,texture_wall_light_head);
		glPopMatrix();
	glEndList();
	// glDeleteTextures(1, &texture_wall_light_head);
	return wall_light_head;
}