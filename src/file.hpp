#ifndef FILE_H
#define FILE_H

void write_file(
	float* dancer_angles,
	float lid_angles,
	bool wall_light,
	bool lamp_light
);

void clear_file();

bool file_is_empty();

#endif