#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>

#include "required.hpp"

using namespace std;

enum axis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

int find_index_x();
int find_index_y();
int find_index_z();

// TODO
float limits[80] = {0};

// Initialize the limits array
void init_limits() {
	// head-neck
	limits[0]=-15;limits[1]=15;
	limits[2]=-60;limits[3]=60;
	limits[4]=-20;limits[5]=20;
	// neck-torso1
	limits[6]=-20;limits[7]=20;
	limits[8]=-10;limits[9]=10;
	limits[10]=-10;limits[11]=10;
	//torso1-torso2
	//torso2-torso3
	//left hip
	//right hip
	//left ankle
	limits[48]=0;limits[49]=30;
	limits[50]=-10;limits[51]=10;
	limits[52]=-10;limits[53]=10;
	//right ankle
	limits[54]= 0;limits[55]=30;
	limits[56]=-10;limits[57]=10;
	limits[58]=-10;limits[59]=10;
	//left wrist
	//right wrist
	//left knee
	//right knee
	//left elbow
	//right elbow

}

// each element in limits stores the extent to which the joint is allowed to rotate
// for joint k, the values limits[2*k] and limits[2*k+1] give the min and max limits respectively
// these values are hardcoded by us

/* Global vars */
float lid_angle = 0;
float box_angle = 0;
float lid_angle_increment = 3.f;
float box_angle_increment = 3.f;

// double neck_angle = 0;
// float neck_angle_increment = 3.f;

float dancer_angles[40] = {0};

/* Variables determining which body part to move */
bool move_box = false; // When true, keyboard keys affect the box. When false, they affect the dancer
bool move_left = true; // When true, keys affect the left side of the dancer. Not valid for joints that have no left or right, for example, the head-neck joint
axis curr_axis = X_AXIS; // Which axis to rotate about. Only valid for joints with three degrees of freedom
short int curr_joint = 0; // Which joint to move

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
	cout << "===INFORMATION===" << endl;

	// Show selected object
	cout << "Selected object:";
	if (move_box) cout << " box" << endl;
	else cout << " dancer" << endl;
	// Show current axis
	switch (curr_axis) {
		case 0:
			cout << "Current axis: X" << endl;
			break;
		case 1:
			cout << "Current axis: Y" << endl;
			break;
		case 2:
			cout << "Current axis: Z" << endl;
			break;
	}
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

	// Show which side is active (only if the joint has three degrees of freedom)
	cout << "Active side: ";
	if (move_left) cout << " left" << endl;
	else cout << " right" << endl;

	cout << "=================" << endl << endl;
}

// Find the index to change in the 'angles' vector
int find_index_x() {
	int index;
	if (curr_joint <= 7) index = find_index_y() - 1;
	else {
		if (curr_joint == 8) index = (move_left ? 36 : 37);
		if (curr_joint == 9) index = (move_left ? 38 : 39);
	}
	return index;
}

int find_index_y() {
	int index;
	switch (curr_joint) {
		case 0: index = 1; break;
		case 1: index = (move_left ? 4 : 7); break;
		case 2: index = 10; break;
		case 3: index = 13; break;
		case 4: index = 16; break;
		case 5: index = 19; break;
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
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void initGL();
void renderGL(int, char**);

void init() {
	initGL();
	init_limits();
}

void initGL() {
  glClearColor(0, 0, 0, 1.f);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST); // enable Z-buffer algorithm
}

/* Callback Definitions */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// draw_box(lid_angle, box_angle);
	draw_dancer(dancer_angles);
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
		case 'l': {
			if (move_left) cout << "Right side active" << endl;
			else cout << "Left side active" << endl;
			move_left = not move_left;
		}
		break;

		// Change the current axis of rotation
		case 'x': {
			cout << "Current axis: X" << endl;
			curr_axis = X_AXIS;
		}
		break;

		case 'y': {
			cout << "Current axis: Y" << endl;
			curr_axis = Y_AXIS;
		}
		break;

		case 'z': {
			cout << "Current axis: Z" << endl;
			curr_axis = Z_AXIS;
		}
		break;

		// Get current information
		case 'i':
			display_info();
			break;

		// Select a joint
		case '0': curr_joint = 0; cout << "Current joint: head-neck\n"; break;
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
			glutPostRedisplay();
			}
		}
		break;
		case 'w': {
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
			glutPostRedisplay();
		}
		break;

		// rotate Y
		case 'a': {
			// check if we have to move the box
			if (move_box) {
				if (box_angle + box_angle_increment <= 90) {
					box_angle += box_angle_increment;
				}
			}
			// we have to move the dancer
			// check how many degrees of freedom the current joint has
			else if (curr_joint <= 7) { // 3 degrees of freedom
				int index = find_index_y();
				if (dancer_angles[index]-3 >= limits[2*index]) {
					dancer_angles[index] -= 3;
				}
			}
			glutPostRedisplay();
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis
		}
		break;
		case 'd': {
			// check if we have to move the box
			if (move_box) {
				if (box_angle - box_angle_increment >= -90) {
					box_angle -= box_angle_increment;
					glutPostRedisplay();
				}
			}
			// we have to move the dancer
			// check how many degrees of freedom the current joint has
			else if (curr_joint <= 7) {
				int index = find_index_y();
				if (dancer_angles[index]+3 <= limits[2*index+1]) {
					dancer_angles[index] += 3;
				}
			}
			glutPostRedisplay();
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis
		}
		break;

		// rotate Z
		case 'q': {
			if (move_box) {}
			else if (curr_joint <= 7) {
				int index = find_index_z();
				if (dancer_angles[index]+3 <= limits[2*index+1]) {
					dancer_angles[index] += 3;
				}
			}
			glutPostRedisplay();
		}
		break;
		case 'e': {
			if (move_box) {}
			else if (curr_joint <= 7) {
				int index = find_index_z();
				if (dancer_angles[index]-3 >= limits[2*index]) {
					dancer_angles[index] -= 3;
				}
			}
			glutPostRedisplay();
		}
		break;

		// case 'j': {
		// 	if (neck_angle - neck_angle_increment >= -60) {
		// 		neck_angle -= neck_angle_increment;
		// 		glutPostRedisplay();
		// 	}
		// }
		// break;

		// case 'k': {
		// 	if (neck_angle + neck_angle_increment <= 60) {
		// 		neck_angle += neck_angle_increment;
		// 		glutPostRedisplay();
		// 	}
		// }
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
