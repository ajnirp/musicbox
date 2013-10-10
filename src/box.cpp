// #include <GLUT/glut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "box.hpp"
#include<string>
#include <stdio.h>

using namespace std;

GLuint LoadTexture(const char* filepath) {
  GLuint texture; 
  unsigned char header[54]; //Supposedly every bmp file has a 54bytes header
  unsigned int position = 54;
  unsigned int width;
  unsigned int height;
  unsigned int imagesize; 
  unsigned char* pixel;

  FILE * bmpfile;
  bmpfile  = fopen(filepath, "rb"); //read a binary file
  if(!bmpfile) {printf("Image not found\n"); return 0;}
  fread(header,1,54,bmpfile);
  width = *(int*)&(header[18]);
  height = *(int*)&(header[22]);
  imagesize = width*height*3;

  pixel = new unsigned char[imagesize];
  fread(pixel,1,imagesize,bmpfile);
  fclose(bmpfile);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixel);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  return texture;
}

// Definitions for the components of the box
int define_base_and_walls() {
	int base_and_walls = glGenLists(1);
	
	GLuint texture = LoadTexture("src/wood.bmp");
	glNewList(base_and_walls, GL_COMPILE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texture);

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
	GLuint texturelid = LoadTexture("src/wood2.bmp");
	glNewList(lid, GL_COMPILE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texturelid);

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

// Definitions for the components of the dancer
// Dancer's head
int define_head() {
	int head = glGenLists(1);
	glNewList(head, GL_COMPILE);
		glColor3ub(165, 42, 42);
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
		glBegin(GL_QUADS);
			glVertex3f(-0.3,0.5,0);
			glVertex3f(0.3,0.5,0);
			glVertex3f(0.3,0.5,-0.5);
			glVertex3f(-0.3,0.5,-0.5);
		glEnd();
		// Top left side
		glColor3ub(165, 112, 42);
		glBegin(GL_QUADS);
			glVertex3f(-0.3,0.5,0);
			glVertex3f(-0.35,0.25,0);
			glVertex3f(-0.35,0.25,-0.5);
			glVertex3f(-0.3,0.5,-0.5);
		glEnd();
		// Bottom left side
		glColor3ub(100, 112, 200);
		glBegin(GL_QUADS);
			glVertex3f(-0.35,0.25,0);
			glVertex3f(-0.25,0,0);
			glVertex3f(-0.25,0,-0.5);
			glVertex3f(-0.35,0.25,-0.5);
		glEnd();
		// Top right side
		glColor3ub(165, 112, 42);
		glBegin(GL_QUADS);
			glVertex3f(0.3,0.5,0);
			glVertex3f(0.35,0.25,0);
			glVertex3f(0.35,0.25,-0.5);
			glVertex3f(0.3,0.5,-0.5);
		glEnd();
		// Bottom right side
		glColor3ub(100, 112, 200);
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
	glNewList(neck, GL_COMPILE);
		glColor3ub(150, 60, 20);
		glScalef(0.25,0.375,0.25);
		glutSolidCube(1);
		glScalef(4,2.67,4); // anti-scale to prevent the head from scaling
	glEndList();
	return neck;
}

// Dancer's top torso (torso1)
int define_torso1() {
	int torso1 = glGenLists(1);
	glNewList(torso1, GL_COMPILE);
		glColor3ub(19, 215, 132);
		glutSolidCube(1);
	glEndList();
	return torso1;
}

// Dancer's middle torso (torso2)
int define_torso2() {
	int torso2 = glGenLists(1);
	glNewList(torso2, GL_COMPILE);
		glColor3ub(83, 164, 39);
		glScalef(0.8,0.25,0.5);	
		glutSolidCube(1);
		glScalef(1.25,4,2);
	glEndList();
	return torso2;
}

// Dancer's bottom torso (torso3)
int define_torso3() {
	int torso3 = glGenLists(1);
	glNewList(torso3, GL_COMPILE);
		glColor3ub(19, 215, 132);
		glScalef(1,0.5,0.5);
		glutSolidCube(1);
		glScalef(1,2,2);
	glEndList();
	return torso3;
}

// Either of the hips of the dancer
int define_hip() {
	int hip = glGenLists(1);
	glNewList(hip, GL_COMPILE);
		glColor3ub(150, 124, 148);
		glScalef(0.125, 0.125, 0.125);
		glutSolidSphere(1,10,10);
		glScalef(8,8,8);
	glEndList();
	return hip;
}

// Either of the thighs of the dancer
int define_thigh() {
	int thigh = glGenLists(1);
	glNewList(thigh, GL_COMPILE);
		glColor3ub(124, 124, 255);
		glScalef(0.25,0.8,0.25);
		glutSolidCube(1);
		glScalef(4,1.25,4);
	glEndList();
	return thigh;
}

// Either of the knees of the dancer
int define_knee() {
	int knee = glGenLists(1);
	glNewList(knee, GL_COMPILE);
		glColor3ub(200, 200, 50);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(1,10,10);
		glScalef(10,10,10);
	glEndList();
	return knee;
}

// Either of the legs of the dancer
int define_leg() {
	int leg = glGenLists(1);
	glNewList(leg, GL_COMPILE);
		glColor3ub(50, 148, 148);

		glScalef(0.25,0.6,0.25);
		glutSolidCube(1);
		glScalef(4,3.33,4);
	glEndList();
	return leg;
}

// Either of the ankles of the dancer
int define_ankle() {
	int ankle = glGenLists(1);
	glNewList(ankle, GL_COMPILE);
		glColor3ub(50,200,50);
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
	glNewList(shoulder, GL_COMPILE);
		glColor3ub(56,56,200);
		glScalef(0.125,0.125,0.125);
		glutSolidSphere(1,10,10);
		glScalef(8,8,8);
	glEndList();
	return shoulder;
}

int define_upper_arm() {
	int upper_arm = glGenLists(1);
	glNewList(upper_arm, GL_COMPILE);
		glColor3ub(160,20,90);
		glScalef(0.2,0.8,0.2);
		glutSolidCube(1);
		glScalef(5,1.25,5);
	glEndList();
	return upper_arm;
}

int define_elbow() {
	int elbow = glGenLists(1);
	glNewList(elbow, GL_COMPILE);
		glColor3ub(45,234,90);
		glScalef(0.1,0.1,0.1);
		glutSolidSphere(1,10,10);
		glScalef(10,10,10);
	glEndList();
	return elbow;
}

int define_lower_arm() {
	int lower_arm = glGenLists(1);
	glNewList(lower_arm, GL_COMPILE);
		glColor3ub(20,20,90);
		glScalef(0.2,0.6,0.2);
		glutSolidCube(1);
		glScalef(5,1.67,5);
	glEndList();
	return lower_arm;
}

int define_wrist() {
	int wrist = glGenLists(1);
	glNewList(wrist, GL_COMPILE);
		glColor3ub(94,87,218);
		glScalef(0.1,0.1,0.1);
		glutSolidSphere(1,10,10);
		glScalef(10,10,10);
	glEndList();
	return wrist;
}

int define_hand() {
	int hand = glGenLists(1);
	glNewList(hand, GL_COMPILE);
		glColor3ub(200,200,10);
		GLUquadric* quad = gluNewQuadric();
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.1,0.15,0.2,10,10);
	glEndList();
	return hand;
}

// Drawing function for the box
void draw_box(double lid_degrees, double box_degrees) {
	int base_and_walls = define_base_and_walls();
	int lid = define_lid();
	glPushMatrix();
		glTranslatef(-2,0,0);
		// glScalef(1,1,2);
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

// Drawing function for the dancer
void draw_dancer(float* angles, float dancer_angle) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons

	// define the various components of the dancer
	int head = define_head();
	int neck = define_neck();

	int torso1 = define_torso1();
	int torso2 = define_torso2();
	int torso3 = define_torso3();

	int left_hip = define_hip();
	int right_hip = define_hip();

	int left_thigh = define_thigh();
	int right_thigh = define_thigh();

	int left_knee = define_knee();
	int right_knee = define_knee();

	int left_ankle = define_ankle();
	int right_ankle = define_ankle();

	int left_leg = define_leg();
	int right_leg = define_leg();

	int left_foot = define_foot();
	int right_foot = define_foot();

	int left_shoulder = define_shoulder();
	int right_shoulder = define_shoulder();

	int left_upper_arm = define_upper_arm();
	int right_upper_arm = define_upper_arm();

	int left_elbow = define_elbow();
	int right_elbow = define_elbow();

	int left_lower_arm = define_lower_arm();
	int right_lower_arm = define_lower_arm();

	int left_wrist = define_wrist();
	int right_wrist = define_wrist();

	int left_hand = define_hand();
	int right_hand = define_hand();

	// torso3 and onwards
	glPushMatrix();
		// glTranslatef(0,2,0);
		// glScalef(1.4,1.4,1.4); // scale the dancer
		glRotatef(dancer_angle,0,1,0);
		glCallList(torso3); // draw torso3
		// torso2 and onwards
		glPushMatrix();
			glTranslatef(0,0.25,0);
			glRotatef(angles[16],0,1,0);
			glRotatef(angles[17],0,0,1);
			glRotatef(angles[15],1,0,0);
			glTranslatef(0,0.125,0);
			glCallList(torso2); // draw torso2
			//torso1 and onwards
			glPushMatrix();
				glRotatef(angles[12],1,0,0);
				glRotatef(angles[13],0,1,0);
				glRotatef(angles[14],0,0,1);
				glTranslatef(0,0.625,0); // translation of torso1 wrt torso2
				glScalef(1,1,0.5);
				glCallList(torso1); //draw torso1
				glScalef(1,1,2); // anti-scale to prevent the other dependent parts from scaling
				// left shoulder
				glPushMatrix();
					glTranslatef(-0.625,0.375,0);
					glCallList(left_shoulder);
					// left upper arm
					glPushMatrix();
						glRotatef(angles[3],1,0,0);
						glRotatef(angles[4],0,1,0);
						glRotatef(angles[5],0,0,1);
						glTranslatef(0,-0.125-0.4,0);
						glCallList(left_upper_arm);
						// left elbow
						glPushMatrix();
							glTranslatef(0,-0.4-0.1,0);
							glCallList(left_elbow);
							// left lower arm
							glPushMatrix();
								glRotatef(angles[38],1,0,0);
								glTranslatef(0,-0.1-0.3,0);
								glCallList(left_lower_arm);
								// left wrist
								glPushMatrix();
									glTranslatef(0,-0.3-0.1,0);
									glCallList(left_wrist);
									// left hand
									glPushMatrix();
										glRotatef(angles[30],1,0,0);
										glRotatef(angles[31],0,1,0);
										glRotatef(angles[32],0,0,1);
										glTranslatef(0,-0.1,0);
										glCallList(left_hand);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				// right shoulder
				glPushMatrix();
					glTranslatef(0.625,0.375,0);
					glCallList(right_shoulder);
					// right upper arm
					glPushMatrix();
						glRotatef(angles[6],1,0,0);
						glRotatef(angles[7],0,1,0);
						glRotatef(angles[8],0,0,1);
						glTranslatef(0,-0.125-0.4,0);
						glCallList(right_upper_arm);
						// right elbow
						glPushMatrix();
							glTranslatef(0,-0.4-0.1,0);
							glCallList(right_elbow);
							// right lower arm
							glPushMatrix();
								glRotatef(angles[39],1,0,0);
								glTranslatef(0,-0.1-0.3,0);
								glCallList(right_lower_arm);
								// right wrist
								glPushMatrix();
									glTranslatef(0,-0.3-0.1,0);
									glCallList(right_wrist);
									// right hand
									glPushMatrix();
										glRotatef(angles[33],1,0,0);
										glRotatef(angles[34],0,1,0);
										glRotatef(angles[35],0,0,1);
										glTranslatef(0,-0.1,0);
										glCallList(right_hand);
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				// neck
				glPushMatrix();
					glTranslatef(0,0.5,0); // translation of neck wrt torso1
					glRotatef(angles[9],1,0,0);
					glRotatef(angles[10],0,1,0);
					glRotatef(angles[11],0,0,1);
					glTranslatef(0,0.1875,0);
					glCallList(neck); // draw the neck
					// head
					glPushMatrix();
						glTranslatef(0,0.1875,0); // translation of head wrt neck
						glRotatef(angles[1], 0, 1, 0);
						glRotatef(angles[0], 1, 0, 0);
						glRotatef(angles[2], 0, 0, 1);
						glTranslatef(0,0,0.25);
						glScalef(1,1.5,1);
						glCallList(head); // draw the head
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		// left hip
		glPushMatrix();
			glTranslatef(-0.25,0,0);
			glRotatef(angles[18],1,0,0);
			glRotatef(angles[19],0,1,0);
			glRotatef(angles[20],0,0,1);
			glTranslatef(0,-0.375,0);
			glCallList(left_hip);
			// left thigh
			glPushMatrix();
				glTranslatef(0,-0.525,0);
				glCallList(left_thigh);
				// left knee
				glPushMatrix();
					glTranslatef(0,-0.5,0);
					glCallList(left_knee);
					// left leg
					glPushMatrix();
						glRotatef(angles[36],1,0,0);
						glTranslatef(0,-0.4,0);
						glCallList(left_leg);
						// left ankle
						glPushMatrix();
							glTranslatef(0,-0.175,0); // not sure how we got -0.175...
							// also, it seems to be independent of the leg length!
							glCallList(left_ankle);
							// left foot
							glPushMatrix();
								glRotatef(angles[24],1,0,0);
								glRotatef(angles[25],0,1,0);
								glRotatef(angles[26],0,0,1);
								glTranslatef(0,-0.025,0.125);
								glCallList(left_foot);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		// right hip
		glPushMatrix();
			glTranslatef(0.25,0,0);
			glRotatef(angles[21],1,0,0);
			glRotatef(angles[22],0,1,0);
			glRotatef(angles[23],0,0,1);
			glTranslatef(0,-0.375,0);
			glCallList(right_hip);
			// right thigh
			glPushMatrix();
				glTranslatef(0,-0.525,0);
				glCallList(right_thigh);
				// right knee
				glPushMatrix();
					glTranslatef(0,-0.5,0);
					glCallList(right_knee);
					// right leg
					glPushMatrix();
						glRotatef(angles[37],1,0,0);
						glTranslatef(0,-0.4,0);
						glCallList(right_leg);
						// right ankle
						glPushMatrix();
							glTranslatef(0,-0.175,0);
							glCallList(right_ankle);
							// right foot
							glPushMatrix();
								glRotatef(angles[27],1,0,0);
								glRotatef(angles[28],0,1,0);
								glRotatef(angles[29],0,0,1);
								glTranslatef(0,-0.025,0.125);
								// glTranslatef(0,-0.025,0);
								glCallList(right_foot);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
