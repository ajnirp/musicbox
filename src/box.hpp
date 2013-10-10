#ifndef BOX_H
#define BOX_H

// Components of the box
int define_base_and_walls();
int define_lid();

// Components of the dancer
int define_head();
int define_neck();

int define_torso1();
int define_torso2();
int define_torso3();

int define_shoulder();
int define_upper_arm();
int define_elbow();
int define_lower_arm();
int define_wrist();
int define_hand();

int define_hip();
int define_thigh();
int define_knee();
int define_leg();
int define_ankle();
int define_foot();

// Extra stuff for the dancer

int define_hat();

// Drawing function for the box
void draw_box(double lid_degrees, double box_degrees);

// Drawing function for the dancer
void draw_dancer(float*,float);

#endif