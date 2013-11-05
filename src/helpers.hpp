#ifndef HELPERS_H
#define HELPERS_H

// Display current information about the program (current joint, which lights are on/off etc.)
void display_info(
	short int curr_joint,
	bool move_left,
	bool lamp_light,
	bool wall_light,
	bool record_mode
);

// Display help on what key to press to perform a certain task
void display_keybindings_help();

// Configure OpenGL
void initGL();

// Initialize the limits array
void init_limits(float* limits);

void init_lists(
	int* room_display_lists
);

// Find the index to change in the 'angles' vector
int find_index_x(int& curr_joint, bool move_left);
int find_index_y(int& curr_joint, bool move_left);
int find_index_z(int& curr_joint, bool move_left);

int define_marker_sphere();
void draw_marker_sphere();

#endif