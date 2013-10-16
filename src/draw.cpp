#include <GL/gl.h>
#include <GL/glut.h>

#include "draw.hpp"
#include "box.hpp"
#include "dancer.hpp"

// Drawing function for the box
void draw_box(double lid_degrees) {
	int base_and_walls = define_base_and_walls();
	int lid = define_lid();
	glPushMatrix();
		glTranslatef(-1.5,0,0);
		// glRotatef(box_degrees, 0, 1, 0);
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
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // comment this out to enable normal fill drawing of polygons

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
		glTranslatef(1.5,-1,0); // translate the entire dancer along the y-axis
		// glScalef(.5,.5,.5); // scale the dancer
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
	glPopMatrix();
}