#include <GL/gl.h>
#include <GL/glut.h>

#include "plane.hpp"
#include "room.hpp"
#include "shapes.hpp"
#include "texture.hpp"

int define_plane() {
	int plane =  glGenLists(1);
	glNewList(plane, GL_COMPILE);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLfloat color[] = {255/255.0f,255/255.0f,255/255.0f,0.1f};
		GLfloat specular[] = {1.f,1.f,1.f,1.f};
		GLfloat shininess[] = {0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);

		glPushMatrix();
			glTranslatef(0,-1,-2);
			glScalef(0.9,0.9,0.9);

			glBegin(GL_QUADS);
				glVertex3f(-6,-3,0);
				glVertex3f(9,-3,0);
				glVertex3f(9,6,0);
				glVertex3f(-6,6,0);
			glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
	glEndList();
	return plane;
}