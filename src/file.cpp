// This file contains methods pertaining to file IO, or checking file properties

#include <fstream>
#include <iostream>
#include <string>

// for stat() we need to include the next three libraries
// also see the man page: man 2 stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "file.hpp"

using namespace std;

void write_file(
	float* dancer_angles,
	float dancer_y,
	float lid_angle
) {
	ofstream keyframes_file;
	string filename = "keyframes.txt";
	keyframes_file.open(filename.c_str(), fstream::app);

	for (int i = 0 ; i < 40 ; i++) keyframes_file << dancer_angles[i] << " ";
	keyframes_file << dancer_y << " ";
	keyframes_file << lid_angle << "\n";

	cout << "Saved keyframe to keyframes.txt\n";

	keyframes_file.close();
}

void clear_file() {
	ofstream keyframes_file;
	string filename = "keyframes.txt";
	keyframes_file.open(filename.c_str());
	keyframes_file.close();
	cout << "Cleared out keyframes.txt\n";
}

bool file_is_empty() {
	// Code taken from http://www.cplusplus.com/forum/windows/10853/
	string filename = "keyframes.txt";
	struct stat filestatus;
	stat(filename.c_str(),&filestatus);
	return (filestatus.st_size == 0);
}