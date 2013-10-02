#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "required.hpp"

using namespace std;

/* Global vars */
double lid_angle = 0;
double box_angle = 0;
float lid_angle_increment = 3.f;
float box_angle_increment = 3.f;

/* Window Parameters */
// int win_width = glutGet(GLUT_SCREEN_WIDTH);
// int win_height = glutGet(GLUT_SCREEN_HEIGHT);
int window_id;

/* Callback Declarations */
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void initGL();
void renderGL(int, char**);

void initGL() {
  // glClearColor(0.2, 0.5, 1.f, 1.f); // light blue background color
  glClearColor(1, 1, 1, 1.f);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST); // enable Z-buffer algorithm

  define_base_and_walls();
  define_lid();
}

/* Callback Definitions */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// draw_table();
	draw_box(lid_angle, box_angle);
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
			cout << "Closing the music box...\n";
			glutDestroyWindow(window_id);
			exit(0);
		}
		break;

		// close the box
		case 's': {
			// don't change the angle if it is already shut
			if (-1*lid_angle >= lid_angle_increment) {
				lid_angle += lid_angle_increment;
				glutPostRedisplay();
			}
		}
		break;

		// open the box
		case 'w': {
			// don't change the angle if it is already fully open
			if (-1*lid_angle <= 180-lid_angle_increment) {
				lid_angle -= lid_angle_increment;
				glutPostRedisplay();
			}
		}
		break;

		// rotate clockwise as seen from above
		case 'a': {
			if (box_angle + box_angle_increment <= 90) {
				box_angle += box_angle_increment;
				glutPostRedisplay();
			}
		}
		break;

		// rotate anti-clockwise as seen from above
		case 'd': {
			if (box_angle - box_angle_increment >= -90) {
				box_angle -= box_angle_increment;
				glutPostRedisplay();
			}
		}
		break;
	}
}

void mouse(int button, int state, int x, int y) {
}

void renderGL(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitWindowPosition(0, 0);

	window_id = glutCreateWindow("Music Box");

	initGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
}

int main(int argc, char** argv) {
	cout << "Opening the music box...\n";
	renderGL(argc, argv);
	return 0;
}