#include <GL/gl.h>
#include <GL/glut.h>

#include "plane.hpp"
#include "room.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_plane(float z) {
	int plane =  glGenLists(1);
	glNewList(plane, GL_COMPILE);
		GLfloat color[] = {255/255.0f,255/255.0f,255/255.0f,0.7f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);

		// glColor4f(1,1,1,0);

		glBegin(GL_QUADS);
			// somehow these values work. Why? I don't know
			glVertex3f(-7,-4,z);
			glVertex3f(10,-4,z);
			glVertex3f(10,7,z);
			glVertex3f(-7,7,z);
		glEnd();
	glEndList();
	return plane;
}