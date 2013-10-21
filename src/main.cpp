#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
// #include <GLUT/glut.h>

#include "draw.hpp"

using namespace std;

int find_index_x();
int find_index_y();
int find_index_z();

float limits[80] = {0};

// Initialize the limits array
void init_limits() {
	// head-neck
	limits[0]=-15;limits[1]=15;
	limits[2]=-60;limits[3]=60;
	limits[4]=-20;limits[5]=20;
	// left shoulder
	limits[6]=-90;limits[7]=40;
	limits[8]=-20;limits[9]=20;
	limits[10]=-50;limits[11]=0;
	// right shoulder
	limits[12]=-90;limits[13]=40;
	limits[14]=-20;limits[15]=20;
	limits[16]=0;limits[17]=50;
	// neck-torso1
	limits[18]=-30;limits[19]=30;
	limits[20]=-60;limits[21]=75;
	limits[22]=-15;limits[23]=15;
	// torso1-torso2
	limits[24]=-20;limits[25]=90;
	limits[26]=-60;limits[27]=60;
	limits[28]=-10;limits[29]=10;
	// torso2-torso3
	limits[30]=-20;limits[31]=40;
	limits[32]=-60;limits[33]=60;
	limits[34]=-10;limits[35]=10;
	// left hip
	limits[36]=-30;limits[37]=30;
	limits[38]=-50;limits[39]=10;
	limits[40]=-10;limits[41]=3;
	// right hip
	limits[42]=-30;limits[43]=30;
	limits[44]=-10;limits[45]=50;
	limits[46]=-3;limits[47]=10;
	// left ankle
	limits[48]=0;limits[49]=30;
	limits[50]=-10;limits[51]=10;
	limits[52]=-10;limits[53]=10;
	// right ankle
	limits[54]= 0;limits[55]=30;
	limits[56]=-10;limits[57]=10;
	limits[58]=-10;limits[59]=10;
	// left wrist
	limits[60]=-60;limits[61]=60;
	limits[62]=-20;limits[63]=20;
	limits[64]=-20;limits[65]=20;
	// right wrist
	limits[66]=-60;limits[67]=60;
	limits[68]=-20;limits[69]=20;
	limits[70]=-20;limits[71]=20;
	// left knee
	limits[72]=0;limits[73]=110;
	// right knee
	limits[74]=0;limits[75]=110;
	// left elbow
	limits[76]=-140;limits[77]=0;
	// right elbow
	limits[78]=-140;limits[79]=0;

}

// each element in limits stores the extent to which the joint is allowed to rotate
// for joint k, the values limits[2*k] and limits[2*k+1] give the min and max limits respectively
// these values are hardcoded by us

/* Global vars */

float world_x_angle = 0;
float world_y_angle = 0;
float world_z_angle = 0;

float lid_angle = 0;
float box_angle = 0;
float lid_angle_increment = 3.f;

float dancer_angles[40] = {0};
float dancer_angle = 0;

float door_angle = 0;

/* Variables determining which body part to move */
bool move_box = false; // When true, keyboard keys affect the box. When false, they affect the dancer
bool move_left = true; // When true, keys affect the left side of the dancer. Not valid for joints that have no left or right, for example, the head-neck joint
short int curr_joint = 0; // Which joint to move

/* Variables determining which light to turn on or off */
bool lamp_light = false;
bool wall_light = false;

/* 
Joint Mappings 
	0 head-neck
	1 shoulder
	2 neck-torso1
	3 torso1-torso2
	4 torso2-torso3
	5 hip
	6 ankle
	7 wrist
	8 knee
	9 elbow
*/

/* Window Parameters */
int window_id;

void display_info() {
	cout << "-------INFORMATION-----------" << endl;

	// Show selected object
	cout << "Selected object:";
	if (move_box) cout << " box" << endl;
	else cout << " dancer" << endl;
	// Show which body joint is active
	switch(curr_joint) {
		case 0: cout << "Current joint: head-neck\n"; break;
		case 1:	cout << "Current joint: shoulder\n"; break;
		case 2:	cout << "Current joint: neck-torso1\n"; break;
		case 3:	cout << "Current joint: torso1-torso2\n"; break;
		case 4:	cout << "Current joint: torso2-torso3\n"; break;
		case 5:	cout << "Current joint: hip\n"; break;
		case 6:	cout << "Current joint: ankle\n"; break;
		case 7:	cout << "Current joint: wrist\n"; break;
		case 8:	cout << "Current joint: knee\n"; break;
		case 9:	cout << "Current joint: elbow\n"; break;
	}
	if (curr_joint > 4) {
		// Show which side is active (only if the joint has three degrees of freedom)
		cout << "Active side: ";
		if (move_left) cout << " left" << endl;
		else cout << " right" << endl;
	}

	cout << "----------------------------" << endl << endl;
}

// Find the index to change in the 'angles' vector
int find_index_x() {
	int index = 0;
	if (curr_joint <= 7) index = find_index_y() - 1;
	else {
		if (curr_joint == 8) index = (move_left ? 36 : 37);
		if (curr_joint == 9) index = (move_left ? 38 : 39);
	}
	return index;
}

int find_index_y() {
	int index = 0;
	switch (curr_joint) {
		case 0: index = 1; break;
		case 1: index = (move_left ? 4 : 7); break;
		case 2: index = 10; break;
		case 3: index = 13; break;
		case 4: index = 16; break;
		case 5: index = (move_left ? 19 : 22); break;
		case 6: index = (move_left ? 25 : 28); break;
		case 7: index = (move_left ? 31 : 34); break;
	}
	return index;
}

int find_index_z() {
	int index = find_index_y() + 1;
	return index;
}

/* Callback Declarations */
void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void initGL();
void renderGL(int, char**);

void init() {
	initGL(); // set up the camera, etc.
	init_limits(); // set up the limits vector
	// dancer_angles[3] = -90; // Heil Hitler!
}

void initGL() {
	glClearColor(0, 0, 0, 1.f);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST); // enable Z-buffer algorithm

	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);

	// GLfloat lightpos[] = {-5,0,0,1};
	// glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	// GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	// GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
	// GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	// glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	// glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	// glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	// glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	// glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	// glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	// glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	// glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	// glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	// glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
}

/* Callback Definitions */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,0,5,0,0,0,0,1,0);

	// if (lamp_light)	glEnable(GL_LIGHT1);
	// else glDisable(GL_LIGHT1);

	// if (wall_light)	glEnable(GL_LIGHT1);
	// else glDisable(GL_LIGHT1);
	
	glPushMatrix();
		glRotatef(world_x_angle, 1,0,0);
		glRotatef(world_y_angle, 0,1,0);
		glRotatef(world_z_angle, 0,0,1);
		draw_all_objects(
			lid_angle,
			dancer_angles, dancer_angle,
			door_angle
		);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	if (h == 0) h = 1; // prevent a division by zero
	float ratio = 1.0f * w / h;
	
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(120, ratio, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,0,3,0,0,0,0,1,0);
}

void keyboard(unsigned char key, int x, int y) {
	if (65 <= key and key <= 90) key += 32; // so that even if caps lock is on, the program still works as expected
	int mod = glutGetModifiers();
	switch(key) {
		case 27: {
			cout << "Exiting the program...\n";
			glutDestroyWindow(window_id);
			exit(0);
		}
		break;

		// Toggle which object to move
		case 't': {
			if (move_box) cout << "Selected dancer" << endl;
			else cout << "Selected box" << endl;
			move_box = not move_box;
		}
		break;

		// Toggle which side is active
		case 'r': {
			if (move_left) cout << "Right side active" << endl;
			else cout << "Left side active" << endl;
			move_left = not move_left;
		}
		break;

		// Get current information
		case 'i':
			display_info();
			break;

		// Select a joint
		case '0':   curr_joint = 0; cout << "Current joint: head-neck\n"; break;
		case '1':	curr_joint = 1;	cout << "Current joint: shoulder\n"; break;
		case '2':	curr_joint = 2;	cout << "Current joint: neck-torso1\n"; break;
		case '3':	curr_joint = 3;	cout << "Current joint: torso1-torso2\n"; break;
		case '4':	curr_joint = 4;	cout << "Current joint: torso2-torso3\n"; break;
		case '5':	curr_joint = 5;	cout << "Current joint: hip\n"; break;
		case '6':	curr_joint = 6;	cout << "Current joint: ankle\n"; break;
		case '7':	curr_joint = 7;	cout << "Current joint: wrist\n"; break;
		case '8':	curr_joint = 8;	cout << "Current joint: knee\n"; break;
		case '9':	curr_joint = 9;	cout << "Current joint: elbow\n"; break;

		// rotate X
		case 's': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_x_angle += 3;
			}
			else {
				if (move_box) {
					// don't change the angle if it is already shut
					if (-1*lid_angle >= lid_angle_increment) {
						lid_angle += lid_angle_increment;
					}
				}
				// all joints whether they have 1 or 3 dofs can rotate
				// about the x-axis
				else {
					int index = find_index_x();
					if (dancer_angles[index]+3 <= limits[2*index+1]) {
						dancer_angles[index] += 3;
					}
				}
			}
			glutPostRedisplay();
		}
		break;
		case 'w': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_x_angle -= 3;
			}
			else {
				if (move_box) {
					// don't change the angle if it is already fully open
					if (-1*lid_angle <= 180-lid_angle_increment) {
						lid_angle -= lid_angle_increment;
					}
				}
				// all joints whether they have 1 or 3 dofs can rotate
				// about the x-axis
				else {
					int index = find_index_x();
					if (dancer_angles[index]-3 >= limits[2*index]) {
						dancer_angles[index] -= 3;
					}
				}
			}
			glutPostRedisplay();
		}
		break;

		// rotate Y
		case 'a': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_y_angle -= 3;
			}
			else {
				if (not(move_box) and curr_joint <= 7) {
					int index = find_index_y();
					if (dancer_angles[index]-3 >= limits[2*index]) {
						dancer_angles[index] -= 3;
					}
				}
			}
			glutPostRedisplay();
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis only
		}
		break;
		case 'd': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_y_angle += 3;
			}
			else {
				// check if we have to move the box
				if (not(move_box) and curr_joint <= 7) {
					int index = find_index_y();
					if (dancer_angles[index]+3 <= limits[2*index+1]) {
						dancer_angles[index] += 3;
					}
				}
			}
			glutPostRedisplay();
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis only
		}
		break;

		// rotate Z
		case 'q': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_z_angle -= 3;
			}
			else {
				if (move_box) {}
				else if (curr_joint <= 7) {
					int index = find_index_z();
					if (dancer_angles[index]+3 <= limits[2*index+1]) {
						dancer_angles[index] += 3;
					}
				}
			}
			glutPostRedisplay();
		}
		break;
		case 'e': {
			if (mod == GLUT_ACTIVE_SHIFT) {
				world_z_angle += 3;
			}
			else {
				if (move_box) {}
				else if (curr_joint <= 7) {
					int index = find_index_z();
					if (dancer_angles[index]-3 >= limits[2*index]) {
						dancer_angles[index] -= 3;
					}
				}
			}
			glutPostRedisplay();
		}
		break;

		case ',': {
			if (not(move_box) and dancer_angle - 3 >= -90) {
				dancer_angle -= 3;
				glutPostRedisplay();
			}
		}
		break;

		case '.': {
			if (not(move_box) and dancer_angle + 3 <= 90) {
				dancer_angle += 3;
				glutPostRedisplay();
			}
		}
		break;

		// reset everything
		case 'h': {
			cout << "Resetting all angles..." << endl;
			for (int i = 0 ; i < 40 ; i++) dancer_angles[i] = 0;
			lid_angle = 0;
			glutPostRedisplay();
		}
		break;

		// toggle lamp light
		case 'l': {
			lamp_light = not lamp_light; 
			cout << "Lamp light is now " << (lamp_light ? "ON" : "OFF") << endl;
		}

		// toggle wall light
		case 'k': {
			wall_light = not wall_light; 
			cout << "Wall light is now " << (wall_light ? "ON" : "OFF") << endl;
		}
	}
}

void mouse(int button, int state, int x, int y) {}

void renderGL(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitWindowPosition(0, 0);

	window_id = glutCreateWindow("Music Box");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
}

int main(int argc, char** argv) {
	renderGL(argc, argv);
	return 0;
}
