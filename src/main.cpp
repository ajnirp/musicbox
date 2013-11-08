#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <utility>

#include <GL/gl.h>
#include <GL/freeglut.h>
// #include <GLUT/glut.h> // uncomment this to compile on OS X

#include "room.hpp"
#include "dancer.hpp"
#include "box.hpp"
#include "draw.hpp"
#include "coordinate.hpp"
#include "bezier.hpp"
#include "helpers.hpp"
#include "file.hpp"

#include "callbacks.hpp"

#define GLUT_FRAME_TIME 50
#define NUM_SAMPLES 50
#define FRAMES_PER_SECOND 30

using namespace std;

float limits[80] = {0};

int num_frames = 30;

// the current and previous keyframes of the animation
vector<float> keyframe1;
vector<float> keyframe2;

// each element in limits stores the extent to which the joint is allowed to rotate
// for joint k, the values limits[2*k] and limits[2*k+1] give the min and max limits respectively
// these values are hardcoded by us

/* Global vars */

bool record_mode = false;
float world_x_angle = 0;
float world_y_angle = 0;
float world_z_angle = 0;
float lid_angle = 0;
float box_angle = 0;
float lid_angle_increment = 3.f;
float dancer_angles[40] = {0};
float dancer_angle = 0;
float dancer_y = 0;
float door_angle = 0;
float plane_z = 0;

unsigned char* pRGB;
unsigned int framenum = 0;
bool dump_frames = false;

/* Variables determining which body part to move */
bool move_left = true; // When true, keys affect the left side of the dancer. Not valid for joints that have no left or right, for example, the head-neck joint
int curr_joint = 0; // Which joint to move. This int takes values between 0 and 9, both included

/* Variables determining which light to turn on or off */
bool lamp_light = true;
bool wall_light = true;

/* Boolean controlling whether the Bezier curve is drawn or not */
bool draw_bezier = false;

/* Boolean controlling whether the animation has started or not */
bool move_camera = false;

/* Camera coordinates */
float camera_x = 0;
float camera_y = 0;
float camera_z = 5;

/* Window Parameters */
int window_id;

/* Display lists */
int room_display_lists[46];

ifstream keyframes_file;

bool animate();
void capture_frame(unsigned int);

// Find the coordinates that were clicked
vector<double>
GetOGLPos(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    posZ = (plane_z * 0.9) - 2;
 	
 	vector<double> result;
 	result.push_back(posX);
 	result.push_back(posY);
 	result.push_back(posZ);

 	return result;
}

void init() {
	keyframes_file.open("keyframes.txt");
	if (!keyframes_file.is_open()) { cout << "Error opening keyframes.txt\n"; exit(1); }
	for (int i = 0 ; i < 42 ; i++) {
		keyframe1.push_back(0);
		keyframe2.push_back(0);
	}
	keyframe1.push_back(30);
	keyframe2.push_back(30);

	initGL(); // set up the camera, etc.
	init_limits(limits); // set up the limits vector
	init_lists(room_display_lists); // set up the display lists
}

void timer(int value) {
	bool animation_continue = true;
	if (value == num_frames) {
		value = 0;
		animation_continue = animate();
	}
	if (animation_continue) {
		num_frames = keyframe1[42];
		for (int i = 0 ; i < 40 ; i++) dancer_angles[i] += (float)(keyframe2[i]-keyframe1[i])/(float)(num_frames);
		dancer_y += (float)(keyframe2[40]-keyframe1[40])/(float)(num_frames);
		lid_angle += (float)(keyframe2[41]-keyframe1[41])/(float)(num_frames);
		value++;
		glutPostRedisplay();
		glutTimerFunc(1000.f/30.f,timer,value);
	}
	else {
		cout << "Animation over\n";
		return;
	}
}

/* Callback Definitions */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// bring camera in front of the box
	camera_x = -2;
	camera_y = 0.9;
	camera_z = -0.8;
	gluLookAt(camera_x,camera_y,camera_z,
		      camera_x,camera_y,camera_z-1,
		      0,1,0);

	if (lamp_light) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);

	if (wall_light) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);

	glPushMatrix();
		glRotatef(world_x_angle, 1,0,0);
		glRotatef(world_y_angle, 0,1,0);
		glRotatef(world_z_angle, 0,0,1);
		draw_all_objects(
			room_display_lists,
			lid_angle,
			dancer_angles, dancer_angle, dancer_y,
			door_angle
		);
	glPopMatrix();

	if (dump_frames) capture_frame(framenum++);
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
}

void keyboard(unsigned char key, int x, int y) {
	if (65 <= key and key <= 90) key += 32; // so that even if caps lock is on, the program still works as expected
	switch(key) {
		case 27: {
			cout << "Exiting the program...\n";
			glutDestroyWindow(window_id);
			// exit(0);
		}
		break;

		// Toggle which side is active
		case 'r': {
			if (move_left) cout << "Right side active" << endl;
			else cout << "Left side active" << endl;
			move_left = not move_left;
		}
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
			// all joints whether they have 1 or 3 dofs can rotate
			// about the x-axis
			int index = find_index_x(curr_joint,move_left);
			// if (dancer_angles[index]+3 <= limits[2*index+1]) {
				dancer_angles[index] += 3;
				glutPostRedisplay();
			// }
		}
		break;
		case 'w': {
			// all joints whether they have 1 or 3 dofs can rotate
			// about the x-axis
			int index = find_index_x(curr_joint,move_left);
			// if (dancer_angles[index]-3 >= limits[2*index]) {
				dancer_angles[index] -= 3;
				glutPostRedisplay();
			// }
		}
		break;

		// rotate Y
		case 'a': {
			if (curr_joint <= 7) {
				int index = find_index_y(curr_joint,move_left);
				// if (dancer_angles[index]-3 >= limits[2*index]) {
					dancer_angles[index] -= 3;
					glutPostRedisplay();
				// }
			}
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis only
		}
		break;
		case 'd': {
			// check if we have to move the box
			if (curr_joint <= 7) {
				int index = find_index_y(curr_joint,move_left);
				// if (dancer_angles[index]+3 <= limits[2*index+1]) {
					dancer_angles[index] += 3;
					glutPostRedisplay();
				// }
			}
			// nothing for 8 and 9 because the knee and elbow rotate about the z-axis only
		}
		break;

		// rotate Z
		case 'q': {
			if (curr_joint <= 7) {
				int index = find_index_z(curr_joint,move_left);
				// if (dancer_angles[index]+3 <= limits[2*index+1]) {
					dancer_angles[index] += 3;
					glutPostRedisplay();
				// }
			}
		}
		break;
		case 'e': {
			if (curr_joint <= 7) {
				int index = find_index_z(curr_joint,move_left);
				// if (dancer_angles[index]-3 >= limits[2*index]) {
					dancer_angles[index] -= 3;
					glutPostRedisplay();
				// }
			}
		}
		break;

		// toggle lamp light
		case 'k': {
			lamp_light = not lamp_light; 
			cout << "Lamp light is now " << (lamp_light ? "ON" : "OFF") << endl;
			glutPostRedisplay();
		}
		break;

		// toggle wall light
		case 'l': {
			wall_light = not wall_light; 
			cout << "Wall light is now " << (wall_light ? "ON" : "OFF") << endl;
			glutPostRedisplay();
		}
		break;

		// open and close door
		case '+': {
			if (door_angle <= 90-3) {
				door_angle += 3;
			}
			glutPostRedisplay();
		}
		break;

		case '-': {
			if (door_angle >= 3) {
				door_angle -= 3;
			}
			glutPostRedisplay();
		}
		break;

		// Get current information
		case 'i': {
			display_info(
				curr_joint,
				move_left,
				lamp_light,
				wall_light,
				record_mode
			);
		}
		break;

		// Move the camera around
		case 't': {
			camera_z -= 0.1;
			glutPostRedisplay();
		}
		break;
		case 'g': {
			camera_z += 0.1;
			glutPostRedisplay();
		}
		break;
		case 'f': {
			camera_x -= 0.1;
			glutPostRedisplay();
		}
		break;
		case 'h': {
			camera_x += 0.1;
			glutPostRedisplay();
		}
		break;

		// Open and close the box
		case 'z': {
			lid_angle -= 2;
			glutPostRedisplay();
		}
		break;
		case 'x': {
			lid_angle += 2;
			glutPostRedisplay();
		}
		break;

		// Move the dancer up and down
		case 'c': {
			dancer_y += 0.1;
			glutPostRedisplay();
		}
		break;
		case 'v': {
			dancer_y -= 0.1;
			glutPostRedisplay();
		}
		break;

		// Output camera coordinates
		case '`': {
			cout << camera_x << " " << camera_y << " " << camera_z << endl;
		}
		break;

		// Dump frames
		case 'p': {
			dump_frames = not dump_frames;
			glutPostRedisplay();
		}
		break;
	}
}

void process_special_keys(int key, int x, int y) {
	switch(key) {
		// Get help
		case GLUT_KEY_F1:
			display_keybindings_help();
			break;

		// reset everything
		case GLUT_KEY_F5: {
			cout << "Resetting everything..." << endl;
			for (int i = 0 ; i < 40 ; i++) dancer_angles[i] = 0;
			lid_angle = 0;
			lamp_light = false;
			wall_light = false;
			glutPostRedisplay();
		}
		break;

		case GLUT_KEY_DOWN: {
			camera_y -= 0.1;
			// plane_z -= 0.1;
			glutPostRedisplay();
		}
		break;

		case GLUT_KEY_UP: {
			// plane_z += 0.1;
			camera_y += 0.1;
			glutPostRedisplay();
		}
		break;

		// Save a keyframe to the keyframes file
		case GLUT_KEY_F3: {
			if (record_mode) {
				write_file(
					dancer_angles,
					dancer_y,
					lid_angle
				);
			}
			else {
				cout << "Currently in playback mode, cannot save keyframes!\n";
			}
		}
		break;

		// Clear the keyframes file
		case GLUT_KEY_F11: {
			clear_file();
		}
		break;
	}
}

void mouse(int button, int state, int x, int y) {
}

void renderGL(int argc, char** argv) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitWindowPosition(0, 0);

	window_id = glutCreateWindow("Music Box");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(process_special_keys);
	glutMouseFunc(mouse);
	
	if (!record_mode) glutTimerFunc(1000,timer,30);

	glutMainLoop();
}

// Animate function
bool animate() {
	keyframe1 = keyframe2;
	if (keyframes_file.good()) {
		// get a new line
		string line;
		getline(keyframes_file, line);
		// clear keyframe2 and read the new split line into it
		string buffer;
		stringstream ss(line);
		keyframe2.clear();
		while (ss >> buffer) keyframe2.push_back(atof(buffer.c_str())); // convert buffer to a float before pushing into keyframe2
		return true;
	}
	else return false;
}

void capture_frame(unsigned int framenum) {
  //global pointer float *pRGB
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];
	// set the framebuffer to read
	//default for double buffered
	glReadBuffer(GL_BACK);

	glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment

	glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
	char filename[200];
	sprintf(filename,"frm/frame_%04d.ppm",framenum);
	ofstream out(filename, std::ios::out);
	out<<"P6"<<endl;
	out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
	out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
	out.close();

	//function to store pRGB in a file named count
	delete pRGB;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Insufficient number of arguments\n";
		exit(1);
	}
	else {
		if (string(argv[1]) == "--help" or (string(argv[1]) == "-h")) {
			cout <<
			"USAGE: ./bin/musicbox <flag> where flag is one of\n             -p   --playback\n             -r   --record\n             -h   --help\n";
			cout << "For detailed help on how to use the program, please read the README in the Github repo: https://wenderen/github/musicbox\n";
			exit(0);
		}
		else if (string(argv[1]) == "--playback" or (string(argv[1]) == "-p")) {
			cout << "Started program in PLAYBACK MODE...\n";
			record_mode = false;
		}
		else if (string(argv[1]) == "--record" or (string(argv[1]) == "-r")) {
			cout << "Started program in RECORD MODE...\n";
			record_mode = true;
		}
		else {
			cout << "ERROR: unrecognized option " << argv[1] << endl;
			exit(1);
		}
	}
	renderGL(argc, argv);
	keyframes_file.close();
	return 0;
}
