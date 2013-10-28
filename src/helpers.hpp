#ifndef HELPERS_H
#define HELPERS_H

// Display current information about the program (current joint, which lights are on/off etc.)
void
display_info(
	short int curr_joint,
	bool move_box,
	bool move_left,
	bool lamp_light,
	bool wall_light
);

// Display help on what key to press to perform a certain task
void
display_keybindings_help();

// Configure OpenGL
void
initGL();

// Initialize the limits array
void
init_limits(float* limits);

#endif