#ifndef FILE_H
#define FILE_H

void write_file(
	float* dancer_angles,
	float dancer_y,
	float lid_angles
);

void clear_file();

bool file_is_empty();

#endif