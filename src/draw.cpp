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

// Drawing function for the box
void draw_box(double lid_degrees) {
	int base_and_walls = define_base_and_walls();
	int lid = define_lid();
	glPushMatrix();
		// glTranslatef(0,2,2);
		glScalef(0.5,0.85,0.5);
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

	int hat = define_hat();
	int stick = define_stick();

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
		// glPopMatrix();
	glPopMatrix();
}

// Drawing function for the table
void draw_table() {
	int table_top = define_table_top();
	int table_leg = define_table_leg();

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
void draw_room(float door_angle) {
	int texture_floor = LoadTexture("tex/room-cropped.bmp");
	int texture_ceiling = LoadTexture("tex/wood4.bmp");

	int room_floor = define_floor(true, texture_floor);
	int room_ceiling = define_ceiling(true, texture_ceiling);

	int room_left_wall = define_side_wall(-6,true); // true because it is the left wall
	int room_right_wall = define_side_wall(9,false); // false because it is the right wall

	int room_front_wall = define_front_wall(true);
	int room_back_wall = define_back_wall(true);

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
			// glCallList(room_front_wall);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(5,0,4);
			// glRotatef(door_angle,0,1,0);
			glRotatef(90,0,1,0);
			glTranslatef(-5,0,-4);
			glCallList(door);
		glPopMatrix();
		
	glPopMatrix();
}

// Drawing function for the one_legged table
void draw_one_legged_table() {
	int one_legged_table_top = define_one_legged_table_top();
	int one_legged_table_leg = define_one_legged_table_leg();
	int one_legged_table_base = define_one_legged_table_base();

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
void draw_chair() {
	int chair_seat = define_chair_seat();
	int chair_leg = define_chair_leg();
	int chair_back = define_chair_back();

	glPushMatrix();
		glScalef(2,2,2);
		glPushMatrix();
			// glTranslatef(0,-1,0);
			// glRotatef(60,0,1,0);
			// glRotatef(90,1,0,0);
			// glRotatef(90,0,0,1);
			// glScalef(2,2,2);
			// glTranslatef(0,-1,0);
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
void draw_stool() {
	int stool_seat = define_stool_seat();
	int stool_leg = define_stool_leg();
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
void draw_lamp() {
	int lamp_stand = define_lamp_stand();
	int lamp_head = define_lamp_head();
	int lamp_base = define_lamp_base();
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
void draw_wall_light() {
	int wall_light_base = define_wall_light_base();
	int wall_light_neck = define_wall_light_neck();
	int wall_light_head = define_wall_light_head();

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
void draw_plane(float z) {
	glPushMatrix();
	glPopMatrix();
	int plane = define_plane(z);
	glCallList(plane);
}

// Draw everything
void draw_all_objects(
	float lid_degrees,
	float* dancer_angles, float dancer_angle,
	float door_angle
) {
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons
	// Room walls and door
	draw_room(door_angle);

	// Box and dancer
	glPushMatrix();
		// glTranslatef(0,2.6001,1.7);
		glTranslatef(-2,2.1+.001,-1);
		draw_box(lid_degrees);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2,0,-2.7);
		draw_dancer(dancer_angles, dancer_angle);
	glPopMatrix();

	// Furniture
	glPushMatrix();
		glTranslatef(-2,-1,-2.7);
		draw_table();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5,-2.05,0);
		draw_one_legged_table();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.5,-2,-2.5);
		glRotatef(-90,0,1,0);
		draw_chair();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-2,0);
		draw_stool();
	glPopMatrix();

	// Lights
	// lamp
	glPushMatrix();
		glTranslatef(-3,-1.5,0);
		draw_lamp();
	glPopMatrix();
	// wall light
	glPushMatrix();
		glTranslatef(4,2,-5);
		glRotatef(-90,0,1,0);
		draw_wall_light();
	glPopMatrix();
}

// Draw the Bezier curve
void draw_bezier_curve(vector<coordinate_t> curve_points, float spacing) {
	int bezier = define_bezier_curve(curve_points, spacing);
	glCallList(bezier);
}