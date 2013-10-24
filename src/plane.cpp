#include <GL/gl.h>
#include <GL/glut.h>

#include "plane.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_plane(int z) {
	int plane =  glGenLists(1);
	glNewList(plane, GL_COMPILE);
		GLfloat color[] = {255/255.0f,255/255.0f,255/255.0f,1.f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
		glBegin(GL_QUADS);
			glVertex3f(-6,-3,z);
			glVertex3f(9,-3,z);
			glVertex3f(9,6,z);
			glVertex3f(-6,6,z);
		glEnd();
	glEndList();
	return plane;
}