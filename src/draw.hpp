#ifndef DRAW_H
#define DRAW_H

// Box and dancer
void draw_box(double lid_degrees);
void draw_dancer(float* angles, float dancer_angle);

// Room walls and door
void draw_room(float door_angle);

// Furniture
void draw_table();
void draw_chair();
void draw_one_legged_table();
void draw_stool();

// Lights
void draw_lamp();
void draw_wall_light();

// Plane
void draw_plane(float z);

// Universal drawing function
void draw_all_objects(
	float lid_degrees,
	float* dancer_angles, float dancer_angle,
	float door_angle
);

#endif