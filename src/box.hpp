#ifndef BOX_H
#define BOX_H

int define_base_and_walls();
int define_lid();

// Extra stuff for the dancer
int define_hat();

// Drawing function for the box
void draw_box(double lid_degrees);

// Drawing function for the dancer
void draw_dancer(float*,float);

#endif