// This file contains functions pertaining to textures

#include "texture.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

GLuint LoadTexture(const char* filepath) {
  GLuint texture; 
  unsigned char header[54]; //Supposedly every bmp file has a 54bytes header
  unsigned int position;
  unsigned int width;
  unsigned int height;
  unsigned int imagesize;
  unsigned char* pixel;

  FILE * bmpfile;
  bmpfile  = fopen(filepath, "rb"); //read a binary file
  if(!bmpfile) {printf("Image not found\n"); return 0;}
  fread(header,1,54,bmpfile);

  position = *(int*)&(header[0x0A]);
  imagesize = *(int*)&(header[0x22]);
  width = *(int*)&(header[18]);
  height = *(int*)&(header[22]);

  if (imagesize == 0) imagesize = width*height*3;
  if (position == 0) position = 54;

  // cout << "Allocating an array of size " << imagesize << endl;
  pixel = new unsigned char[imagesize];
  fread(pixel,1,imagesize,bmpfile);
  fclose(bmpfile);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixel);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

  delete [] pixel; // prevent memory leaks due to repeated heap allocation
  return texture;
}

GLuint texture_room1() {
  return LoadTexture("tex/room-cropped.bmp");
}

GLuint texture_room2() {
  return LoadTexture("tex/wood4.bmp");
}