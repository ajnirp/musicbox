// This file contains drawing functions for each object in the world

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#include "draw.hpp"
#include "box.hpp"
#include "dancer.hpp"
#include "room.hpp"
#include "texture.hpp"
#include "plane.hpp"
#include "bezier.hpp"
#include "painting.hpp"

#include <iostream>
using namespace std;

// Drawing function for the box
void draw_box(int* room_display_lists, double lid_degrees) {
	int base_and_walls = room_display_lists[6];
	int lid = define_lid();
	glPushMatrix();
		glScalef(0.5,0.85,0.5);
		// glRotatef(90,0,1,0);
		// draw the lid
		glPushMatrix();
			glTranslatef(0, -2, -5);
			glRotatef(lid_degrees,1,0,0);
			glTranslatef(0, 2, 5);
			glCallList(lid);
		glPopMatrix();
		// draw the base and walls
		glCallList(base_and_walls);
	glPopMatrix();
}

// Drawing function for the dancer
void draw_dancer(int* room_display_lists, float* angles, float dancer_angle) {
	// define the various components of the dancer
	int head = room_display_lists[7];
	int neck = room_display_lists[8];

	int torso1 = room_display_lists[9];
	int torso2 = room_display_lists[10];
	int torso3 = room_display_lists[11];

	int left_hip = room_display_lists[12];
	int right_hip = room_display_lists[13];

	int left_thigh = room_display_lists[14];
	int right_thigh = room_display_lists[14];
	int left_knee = room_display_lists[15];
	int right_knee = room_display_lists[15];
	int left_ankle = room_display_lists[16];
	int right_ankle = room_display_lists[16];
	int left_leg = room_display_lists[17];
	int right_leg = room_display_lists[17];
	int left_foot = room_display_lists[18];
	int right_foot = room_display_lists[18];

	int left_shoulder = room_display_lists[19];
	int right_shoulder = room_display_lists[19];
	int left_upper_arm = room_display_lists[20];
	int right_upper_arm = room_display_lists[20];
	int left_elbow = room_display_lists[21];
	int right_elbow = room_display_lists[21];
	int left_lower_arm = room_display_lists[22];
	int right_lower_arm = room_display_lists[22];
	int left_wrist = room_display_lists[23];
	int right_wrist = room_display_lists[23];
	int left_hand = room_display_lists[24];
	int right_hand = room_display_lists[24];

	int hat = room_display_lists[25];
	int stick = room_display_lists[26];

	// torso3 and onwards
	glPushMatrix();
		glTranslatef(0,-0.3,0); // translate the entire dancer along the y-axis
		glScalef(.2,.2,.2); // scale the dancer
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
				glCallList(torso1); //draw torso1
				// left shoulder
				glPushMatrix();
					glTranslatef(-0.625,0.375,0);
					glCallList(left_shoulder);
					// left upper arm
					glPushMatrix();
						glRotatef(angles[3],1,0,0);
						glRotatef(angles[4],0,1,0);
						glRotatef(-5+angles[5],0,0,1);
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
						glRotatef(5+angles[8],0,0,1);
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
										// walking stick
										glPushMatrix();
											glTranslatef(0,0,0.2+1);
											glRotatef(90,1,0,0);
											glCallList(stick);
										glPopMatrix();
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
						// hat
						glPushMatrix();
							glTranslatef(0,0.5,0);
							glCallList(hat);
						glPopMatrix();
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
						glTranslatef(0,-0.05,0);
						glRotatef(angles[36],1,0,0);
						glTranslatef(0,-0.5,0);
						glCallList(left_leg);
						// left ankle
						glPushMatrix();
							glTranslatef(0,-0.525,0);
							glCallList(left_ankle);
							// left foot
							glPushMatrix();
								glTranslatef(0,-0.025,0);
								glRotatef(angles[24],1,0,0);
								glRotatef(angles[25],0,1,0);
								glRotatef(angles[26],0,0,1);
								glTranslatef(0,0,0.125);
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
						glTranslatef(0,-0.05,0);
						glRotatef(angles[37],1,0,0);
						glTranslatef(0,-0.5,0);
						glCallList(right_leg);
						// right ankle
						glPushMatrix();
							glTranslatef(0,-0.525,0);
							glCallList(right_ankle);
							// right foot
							glPushMatrix();
								glTranslatef(0,-0.025,0);
								glRotatef(angles[27],1,0,0);
								glRotatef(angles[28],0,1,0);
								glRotatef(angles[29],0,0,1);
								glTranslatef(0,0,0.125);
								glCallList(right_foot);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the table
void draw_table(int* room_display_lists) {
	int table_top = room_display_lists[27];
	int table_leg = room_display_lists[28];

	glPushMatrix();
		// glTranslatef(0,-1.5,0);
		glCallList(table_top);
		glPushMatrix();
			glColor3ub(100,100,50);
			glTranslatef(-2+0.0625,-0.125-1,1-0.0625);
			glCallList(table_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2-0.0625,-0.125-1,1-0.0625);
			glCallList(table_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2-0.0625,-0.125-1,-1+0.0625);
			glCallList(table_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2+0.0625,-0.125-1,-1+0.0625);
			glCallList(table_leg);
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the room walls
void draw_room(
	int* room_display_lists,
	float door_angle
) {
	int room_floor = room_display_lists[0];
	int room_ceiling = room_display_lists[1];
	int room_left_wall = room_display_lists[2];
	int room_right_wall = room_display_lists[3];
	int room_front_wall = room_display_lists[4];
	int room_back_wall = room_display_lists[5];

	int door = define_door();

	glPushMatrix();
		glTranslatef(0,-1,-2);
		glScalef(0.9,0.9,0.9);

		glPushMatrix();
			glCallList(room_floor);
			glCallList(room_ceiling);

			glCallList(room_left_wall);
			glCallList(room_right_wall);

			glCallList(room_back_wall);
			glCallList(room_front_wall);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5,0,4);
			glRotatef(door_angle,0,1,0);
			// glRotatef(90,0,1,0);
			glTranslatef(-5,0,-4);
			glCallList(door);
		glPopMatrix();
		
	glPopMatrix();

	// glDeleteTextures(1, &texture_floor);
	// glDeleteTextures(1, &texture_ceiling);
}

// Drawing function for the one_legged table
void draw_one_legged_table(int* room_display_lists) {
	int one_legged_table_top = room_display_lists[29];
	int one_legged_table_leg = room_display_lists[30];
	int one_legged_table_base = room_display_lists[31];

	// glMaterialfv()
	glPushMatrix();
		glCallList(one_legged_table_leg);
		glPushMatrix();
			glTranslatef(0,0.75+0.05,0);
			glCallList(one_legged_table_top);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,-0.75-0.05,0);
			glCallList(one_legged_table_base);
		glPopMatrix();
	glPopMatrix();	
}

// Drawing function for the chair
void draw_chair(int* room_display_lists) {
	int chair_seat = room_display_lists[32];
	int chair_leg = room_display_lists[33];
	int chair_back = room_display_lists[34];

	glPushMatrix();
		glScalef(2,2,2);
		glPushMatrix();
			// chair seat
			glCallList(chair_seat);
			// front left leg
			glPushMatrix();
				glTranslatef(-0.35+0.05,-0.05-0.35,0.35-0.05);
				glCallList(chair_leg);
			glPopMatrix();
			// front right leg
			glPushMatrix();
				glTranslatef(0.35-0.05,-0.05-0.35,0.35-0.05);
				glCallList(chair_leg);
			glPopMatrix();
			// back right leg
			glPushMatrix();
				glTranslatef(0.35-0.05,-0.05-0.35,-0.35+0.05);
				glCallList(chair_leg);
			glPopMatrix();
			// back left leg
			glPushMatrix();
				glTranslatef(-0.35+0.05,-0.05-0.35,-0.35+0.05);
				glCallList(chair_leg);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.05+0.6,-0.35+0.05);
				glCallList(chair_back);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the stool
void draw_stool(int* room_display_lists) {
	int stool_seat = room_display_lists[35];
	int stool_leg = room_display_lists[36];
	glPushMatrix();
		// glTranslatef(4,0,0);
		glCallList(stool_seat);
		glPushMatrix();
			glTranslatef(0,-0.05-0.5,-0.7+0.05);
			glCallList(stool_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1*(0.35-0.035)*sqrt(3),-0.05-0.5,(0.35-0.035));
			glCallList(stool_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef((0.35-0.035)*sqrt(3),-0.05-0.5,(0.35-0.035));
			glCallList(stool_leg);
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the lamp
void draw_lamp(int* room_display_lists) {
	int lamp_stand = room_display_lists[37];
	int lamp_head = room_display_lists[38];
	int lamp_base = room_display_lists[39];
	// int lamp_light = define_lamp_light();

	// lamp stand
	glPushMatrix();
		// glTranslatef(0,-1,0);
		glCallList(lamp_stand);
		// lamp head
		glPushMatrix();
			glTranslatef(0,1.5,0);
			glCallList(lamp_head);
		glPopMatrix();
		// lamp base
		glPushMatrix();
			glTranslatef(0,-1.5-0.05,0);
			glCallList(lamp_base);
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the wall light
void draw_wall_light(int* room_display_lists) {
	int wall_light_base = room_display_lists[40];
	int wall_light_neck = room_display_lists[41];
	int wall_light_head = room_display_lists[42];
	glPushMatrix();
		glRotatef(90,0,1,0);
		glScalef(1.5,1.5,1.5);
		glCallList(wall_light_base);
		glPushMatrix();
			glTranslatef(0,0,0.05+0.2);
			glCallList(wall_light_neck);
			glPushMatrix();
				glTranslatef(0,0.2,0.2+0.2);
				glCallList(wall_light_head);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

// Drawing function for the plane
void draw_plane(int* room_display_lists, float plane_z) {
	int plane = room_display_lists[43];
	glPushMatrix();
		glTranslatef(0,0,plane_z);
		glCallList(plane);
	glPopMatrix();
}

// Drawing function for the painting
void draw_painting(int* room_display_lists) {
	int painting = room_display_lists[44];
	cout << "Drawing painting" << endl;
	glCallList(painting);
}

// Draw everything
void draw_all_objects(
	int* room_display_lists,
	float lid_degrees,
	float* dancer_angles, float dancer_angle,float dancer_y,
	float door_angle
) {
	// int* room_display_lists = all_display_lists[0];

	// Room walls and door
	draw_room(room_display_lists, door_angle);

	// Box and dancer
	glPushMatrix();
		// glTranslatef(0,2.6001,1.7);
		glTranslatef(-2,2.1+.001,-1);
		draw_box(room_display_lists ,lid_degrees);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2,dancer_y,-2.7);
		draw_dancer(room_display_lists, dancer_angles, dancer_angle);
	glPopMatrix();

	// Furniture
	glPushMatrix();
		glTranslatef(-2,-1,-2.7);
		draw_table(room_display_lists);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5,-2.05,0);
		draw_one_legged_table(room_display_lists);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.5,-2,-2.5);
		glRotatef(-90,0,1,0);
		draw_chair(room_display_lists);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-2,0);
		draw_stool(room_display_lists);
	glPopMatrix();

	// Lights
	// lamp
	glPushMatrix();
		glTranslatef(-3,-1.5,0);
		draw_lamp(room_display_lists);
	glPopMatrix();
	// wall light
	glPushMatrix();
		glTranslatef(4,2,-5);
		glRotatef(-90,0,1,0);
		draw_wall_light(room_display_lists);
	glPopMatrix();

	// painting
	// glPushMatrix();
	// 	glTranslatef(0,-1,-2);
	// 	glScalef(0.9,0.9,0.9);
	// 	draw_painting(room_display_lists);
	// glPopMatrix();
}

// Draw the Bezier curve
void draw_bezier_curve(vector<coordinate_t> curve_points) {
	int bezier = define_bezier_curve(curve_points);
	glCallList(bezier);
}