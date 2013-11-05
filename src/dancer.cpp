// This file contains definitions for the components of the wooden dancing doll

#include <GL/gl.h>
#include <GL/glut.h>
#include "dancer.hpp"
#include "shapes.hpp"
#include "texture.hpp"
#include <cmath>

// Dancer's head
int define_head() {
	int head = glGenLists(1);
	glNewList(head, GL_COMPILE);
		GLfloat color[] = {205/255.0f,175/255.0f,149/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {1};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		// Front face
		glBegin(GL_POLYGON);
			glVertex3f(-0.25,0,0);
			glVertex3f(0.25,0,0);
			glVertex3f(0.35,0.25,0);
			glVertex3f(0.3,0.5,0);
			glVertex3f(-0.3,0.5,0);
			glVertex3f(-0.35,0.25,0);
		glEnd();

		// Back face
		glBegin(GL_POLYGON);
			glVertex3f(-0.25,0,-0.5);
			glVertex3f(0.25,0,-0.5);
			glVertex3f(0.35,0.25,-0.5);
			glVertex3f(0.3,0.5,-0.5);
			glVertex3f(-0.3,0.5,-0.5);
			glVertex3f(-0.35,0.25,-0.5);
		glEnd();
		// Scalp
		GLfloat color2[] = {100/255.0f,240/255.0f,120/255.0f,1.f};
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color2);
		glBegin(GL_QUADS);
			glVertex3f(-0.3,0.5,0);
			glVertex3f(0.3,0.5,0);
			glVertex3f(0.3,0.5,-0.5);
			glVertex3f(-0.3,0.5,-0.5);
		glEnd();
		// Top left side
		GLfloat color3[] = {165/255.0f,112/255.0f,42/255.0f,1.f};
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color3);
		glBegin(GL_QUADS);
			glVertex3f(-0.3,0.5,0);
			glVertex3f(-0.35,0.25,0);
			glVertex3f(-0.35,0.25,-0.5);
			glVertex3f(-0.3,0.5,-0.5);
		glEnd();
		// Bottom left side
		GLfloat color4[] = {100/255.0f,112/255.0f,200/255.0f,1.f};
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color4);
		glBegin(GL_QUADS);
			glVertex3f(-0.35,0.25,0);
			glVertex3f(-0.25,0,0);
			glVertex3f(-0.25,0,-0.5);
			glVertex3f(-0.35,0.25,-0.5);
		glEnd();
		// Top right side
		GLfloat color5[] = {165/255.0f,112/255.0f,42/255.0f,1.f};
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color5);
		glBegin(GL_QUADS);
			glVertex3f(0.3,0.5,0);
			glVertex3f(0.35,0.25,0);
			glVertex3f(0.35,0.25,-0.5);
			glVertex3f(0.3,0.5,-0.5);
		glEnd();
		// Bottom right side
		GLfloat color6[] = {100/255.0f,112/255.0f,200/255.0f,1.f};
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color6);
		glBegin(GL_QUADS);
			glVertex3f(0.35,0.25,0);
			glVertex3f(0.25,0,0);
			glVertex3f(0.25,0,-0.5);
			glVertex3f(0.35,0.25,-0.5);
		glEnd();
		// Chin
		glBegin(GL_QUADS);
			glVertex3f(-0.25,0,0);
			glVertex3f(0.25,0,0);
			glVertex3f(0.25,0,-0.5);
			glVertex3f(-0.25,0,-0.5);
		glEnd();
	glEndList();
	return head;
}

// Dancer's neck
int define_neck() {
	int neck = glGenLists(1);
	GLuint texture_neck = LoadTexture("tex/wood2.bmp");
	glNewList(neck, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.125,.125,.375,texture_neck);
	glEndList();
	// glDeleteTextures(1, &texture_neck);
	return neck;
}

// Dancer's top torso (torso1)
int define_torso1() {
	int torso1 = glGenLists(1);
	GLuint texture_torso1 = LoadTexture("tex/wood2.bmp");
	glNewList(torso1, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(0.5,0.4,1,texture_torso1);
	glEndList();
	// glDeleteTextures(1, &texture_torso1);
	return torso1;
}

// Dancer's middle torso (torso2)
int define_torso2() {
	int torso2 = glGenLists(1);
	GLuint texture_torso2 = LoadTexture("tex/wood.bmp");
	glNewList(torso2, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.4,.4,.4,texture_torso2);
	glEndList();
	// glDeleteTextures(1, &texture_torso2);
	return torso2;
}

// Dancer's bottom torso (torso3)
int define_torso3() {
	int torso3 = glGenLists(1);
	GLuint texture_torso3 = LoadTexture("tex/wood2.bmp");
	glNewList(torso3, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.4,.4,.5,texture_torso3);
	glEndList();
	// glDeleteTextures(1, &texture_torso3);
	return torso3;
}

// Either of the hips of the dancer
int define_hip() {
	int hip = glGenLists(1);
	GLuint texture_hip = LoadTexture("tex/wood.bmp");
	glNewList(hip, GL_COMPILE);
		// glColor3ub(150, 124, 148);
		glColor3f(1,1,1);
		// glScalef(0.125, 0.125, 0.125);
		// glutSolidSphere(1,10,10);
		// glScalef(8,8,8);
		define_sphere(.125,texture_hip);
	glEndList();
	// glDeleteTextures(1, &texture_hip);
	return hip;
}

// Either of the thighs of the dancer
int define_thigh() {
	int thigh = glGenLists(1);
	GLuint texture_thigh = LoadTexture("tex/wood2.bmp");
	glNewList(thigh, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.125,.125,.8,texture_thigh);
	glEndList();
	// glDeleteTextures(1, &texture_thigh);
	return thigh;
}

// Either of the knees of the dancer
int define_knee() {
	int knee = glGenLists(1);
	GLuint texture_knee = LoadTexture("tex/wood.bmp");
	glNewList(knee, GL_COMPILE);
		glColor3f(1,1,1);
		define_sphere(.1,texture_knee);
	glEndList();
	// glDeleteTextures(1, &texture_knee);
	return knee;
}

// Either of the legs of the dancer
int define_leg() {
	int leg = glGenLists(1);
	GLuint texture_leg = LoadTexture("tex/wood2.bmp");
	glNewList(leg, GL_COMPILE);
		glColor3f(1, 1, 1);
		define_cylinder(.125,.125,1,texture_leg);
	glEndList();
	// glDeleteTextures(1, &texture_leg);
	return leg;
}

// Either of the ankles of the dancer
int define_ankle() {
	int ankle = glGenLists(1);
	glNewList(ankle, GL_COMPILE);
		glColor3ub(139,119,101);
		glScalef(0.2,0.05,0.2);
		glutSolidCube(1);
		glScalef(5,20,5);
	glEndList();
	return ankle;
}

// Either of the feet of the dancer
int define_foot() {
	int feet = glGenLists(1);
	glNewList(feet, GL_COMPILE);
		glColor3ub(100, 50, 50);
		// Top of the foot
		glBegin(GL_QUADS);
			glVertex3f(-0.125,0,0); // A
			glVertex3f(0.125,0,0);  // B
			glVertex3f(0.125,0,-0.25);  // C
			glVertex3f(-0.125,0,-0.25); // D
		glEnd();
		// Sole of the foot
		glBegin(GL_QUADS);
			glVertex3f(-0.125,-0.1,0.15); // E
			glVertex3f(0.125,-0.1,0.15); // F
			glVertex3f(0.125,-0.1,-0.25); // G
			glVertex3f(-0.125,-0.1,-0.25); // H
		glEnd();
		// Left face of the foot
		glBegin(GL_QUADS);
			glVertex3f(-0.125,0,0); // A
			glVertex3f(-0.125,0,-0.25); // D
			glVertex3f(-0.125,-0.1,-0.25); // H
			glVertex3f(-0.125,-0.1,0.15); // E
		glEnd();
		// Right face of the foot
		glBegin(GL_QUADS);
			glVertex3f(0.125,0,0); // B
			glVertex3f(0.125,0,-0.25); // C
			glVertex3f(0.125,-0.1,-0.25); // G
			glVertex3f(0.125,-0.1,0.15); // F
		glEnd();
	glEndList();
	return feet;
}

int define_shoulder() {
	int shoulder = glGenLists(1);
	GLuint texture_shoulder = LoadTexture("tex/wood.bmp");
	glNewList(shoulder, GL_COMPILE);
		glColor3f(1,1,1);
		define_sphere(.13,texture_shoulder);
	glEndList();
	// glDeleteTextures(1, &texture_shoulder);
	return shoulder;
}

int define_upper_arm() {
	int upper_arm = glGenLists(1);
	GLuint texture_upper_arm = LoadTexture("tex/wood2.bmp");
	glNewList(upper_arm, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.1,.1,.8,texture_upper_arm);
	glEndList();
	// glDeleteTextures(1, &texture_upper_arm);
	return upper_arm;
}

int define_elbow() {
	int elbow = glGenLists(1);
	GLuint texture_elbow = LoadTexture("tex/wood.bmp");
	glNewList(elbow, GL_COMPILE);
		glColor3f(1,1,1);
		define_sphere(.1,texture_elbow);
	glEndList();
	// glDeleteTextures(1, &texture_elbow);
	return elbow;
}

int define_lower_arm() {
	int lower_arm = glGenLists(1);
	GLuint texture_lower_arm = LoadTexture("tex/wood2.bmp");
	glNewList(lower_arm, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.1,.1,.6,texture_lower_arm);
	glEndList();
	// glDeleteTextures(1, &texture_lower_arm);
	return lower_arm;
}

int define_wrist() {
	int wrist = glGenLists(1);
	GLuint texture_wrist = LoadTexture("tex/wood.bmp");
	glNewList(wrist, GL_COMPILE);
		glColor3f(1,1,1);
		define_sphere(.1,texture_wrist);
	glEndList();
	// glDeleteTextures(1, &texture_wrist);
	return wrist;
}

int define_hand() {
	int hand = glGenLists(1);
	glNewList(hand, GL_COMPILE);
		glColor3ub(100, 50, 50);
		GLUquadric* quad = gluNewQuadric();
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.1,0.15,0.2,10,10);
	glEndList();
	return hand;
}

int define_hat() {
	int hat = glGenLists(1);
	glNewList(hat, GL_COMPILE);
		// glColor3ub(100,50,50);

		GLfloat color[] = {100/255.0f,50/255.0f,50/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);

		GLUquadric* base = gluNewQuadric();
		GLUquadric* top = gluNewQuadric();
		glTranslatef(0,0,-0.25); // because depth of the head = 0.5
		glRotatef(-90,1,0,0);
		gluCylinder(base,0.6,0.6,0.05,10,10); // base wall
		glBegin(GL_POLYGON); // base of the hat
			for (int i = 0 ; i < 360 ; i++) {
				glVertex3f(0.6*cos(i),0.6*sin(i),0);
			}
		glEnd();
		glPushMatrix();
			gluCylinder(top,0.4,0.4,0.4,10,10); // top wall
		glPopMatrix();
	glEndList();
	return hat;
}

int define_stick() {
	int stick = glGenLists(1);
	GLuint texture_stick = LoadTexture("tex/wood.bmp");
	glNewList(stick, GL_COMPILE);
		glColor3f(1,1,1);
		define_cylinder(.05,.05,2,texture_stick);
	glEndList();
	// glDeleteTextures(1, &texture_stick);
	return stick;
}