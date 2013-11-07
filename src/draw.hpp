#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include "coordinate.hpp"

using namespace std;

// Box and dancer
void draw_box(double lid_degrees);
void draw_dancer(float* angles, float dancer_angle);

// Room walls and door
void draw_room(
	int* room_display_lists,
	float door_angle
);

// Furniture
void draw_table();
void draw_chair();
void draw_one_legged_table();
void draw_stool();

// Lights
void draw_lamp();
void draw_wall_light();

// Plane
void draw_plane(int* room_display_lists, float plane_z);

// Universal drawing function
void draw_all_objects(
	int* room_display_lists,
	float lid_degrees,
	float* dancer_angles, float dancer_angle, float dancer_y,
	float door_angle
);

// Bezier curve
void draw_bezier_curve(vector<coordinate_t> curve_points);

#endif